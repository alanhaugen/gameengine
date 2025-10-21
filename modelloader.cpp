// ModelLoader.cpp - robust version, paste & run (replace your existing file)
#include "ModelLoader.h"
#include "External/tiny_obj_loader.h"
#include <qdebug.h>
#include <qlogging.h>
#include <unordered_map>
#include "External/stb_image.h"
#include <cstring>
#include <stdexcept>
#include <limits>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

namespace std {
template<> struct hash<Vertex> {
    size_t operator()(Vertex const& vertex) const {
        return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
    }
};
}

namespace bbl
{
// Equality operator for vertices
bool operator==(const Vertex& a, const Vertex& b) {
    return a.pos == b.pos && a.color == b.color && a.texCoord == b.texCoord;
}

ModelLoader::ModelLoader(VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue)
    : mDevice(device), mPhysicalDevice(physicalDevice), mCommandPool(commandPool), mGraphicsQueue(graphicsQueue) {}

// Helper: safe check for index range
static inline bool safe_attrib_vertex_exists(const tinyobj::attrib_t& attrib, int vertex_index) {
    if (vertex_index < 0) return false;
    size_t required = static_cast<size_t>(3 * vertex_index + 2);
    return required < attrib.vertices.size();
}
static inline bool safe_attrib_texcoord_exists(const tinyobj::attrib_t& attrib, int texcoord_index) {
    if (texcoord_index < 0) return false;
    size_t required = static_cast<size_t>(2 * texcoord_index + 1);
    return required < attrib.texcoords.size();
}

void ModelLoader::loadModel(const std::string& modelPath, std::vector<Entity>& outEntities, const std::string& customTexturePath)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelPath.c_str())) {
        qDebug() << "Model loading failed:" << warn.c_str() << err.c_str();
        throw std::runtime_error(warn + err);
    }

    std::string modelDir = modelPath.substr(0, modelPath.find_last_of("/\\") + 1);

    for (size_t s = 0; s < shapes.size(); ++s)
    {
        const auto& shape = shapes[s];

        if (shape.mesh.indices.empty()) {
            qDebug() << "Skipping shape" << (int)s << " — empty indices";
            continue;
        }

        Entity entity;
        mesh meshComp;
        meshComp.mEntityId = entity.getEntityId();

        // Build vertices & indices safely
        std::unordered_map<Vertex, uint32_t> uniqueVertices;
        meshComp.mVertices.clear();
        meshComp.mIndices.clear();

        for (const auto& index : shape.mesh.indices)
        {
            // tinyobj: negative indices indicate missing attribute
            if (!safe_attrib_vertex_exists(attrib, index.vertex_index)) {
                qDebug() << "Warning: skipping index with invalid vertex_index =" << index.vertex_index;
                continue; // skip bad index
            }

            Vertex vertex{};
            int vi = index.vertex_index;
            vertex.pos = {
                attrib.vertices[3 * vi + 0],
                attrib.vertices[3 * vi + 1],
                attrib.vertices[3 * vi + 2]
            };

            if (safe_attrib_texcoord_exists(attrib, index.texcoord_index)) {
                vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1] // Flip Y
                };
            } else {
                vertex.texCoord = {0.0f, 0.0f};
            }

            vertex.color = {1.0f, 1.0f, 1.0f};

            auto it = uniqueVertices.find(vertex);
            if (it == uniqueVertices.end()) {
                uint32_t newIndex = static_cast<uint32_t>(meshComp.mVertices.size());
                uniqueVertices[vertex] = newIndex;
                meshComp.mVertices.push_back(vertex);
                meshComp.mIndices.push_back(newIndex);
            } else {
                meshComp.mIndices.push_back(it->second);
            }
        }

        qDebug() << "Shape" << (int)s << "vertices:" << meshComp.mVertices.size() << "indices:" << meshComp.mIndices.size();

        // If we ended up with zero real vertices/indices, skip the shape
        if (meshComp.mVertices.empty() || meshComp.mIndices.empty()) {
            qDebug() << "Skipping shape" << (int)s << " — produced zero vertices or indices after sanitization";
            continue;
        }

        // Initialize handles to null in case creation fails
        meshComp.mVertexBuffer = VK_NULL_HANDLE;
        meshComp.mVertexBufferMemory = VK_NULL_HANDLE;
        meshComp.mIndexBuffer = VK_NULL_HANDLE;
        meshComp.mIndexBufferMemory = VK_NULL_HANDLE;

        // Try to create Vulkan buffers, but don't let one failing shape crash the whole loader.
        bool buffersOk = true;
        try {
            createVertexBuffer(meshComp.mVertices, meshComp.mVertexBuffer, meshComp.mVertexBufferMemory);
        } catch (const std::exception& e) {
            qDebug() << "createVertexBuffer failed for shape" << (int)s << ":" << e.what();
            buffersOk = false;
        }

        try {
            createIndexBuffer(meshComp.mIndices, meshComp.mIndexBuffer, meshComp.mIndexBufferMemory);
        } catch (const std::exception& e) {
            qDebug() << "createIndexBuffer failed for shape" << (int)s << ":" << e.what();
            buffersOk = false;
        }

        if (!buffersOk || meshComp.mVertexBuffer == VK_NULL_HANDLE || meshComp.mIndexBuffer == VK_NULL_HANDLE) {
            qDebug() << "Skipping shape" << (int)s << " — buffer creation failed";
            // Clean up any partial allocations if applicable (safe-guard)
            if (meshComp.mVertexBuffer != VK_NULL_HANDLE) {
                vkDestroyBuffer(mDevice, meshComp.mVertexBuffer, nullptr);
                meshComp.mVertexBuffer = VK_NULL_HANDLE;
            }
            if (meshComp.mVertexBufferMemory != VK_NULL_HANDLE) {
                vkFreeMemory(mDevice, meshComp.mVertexBufferMemory, nullptr);
                meshComp.mVertexBufferMemory = VK_NULL_HANDLE;
            }
            if (meshComp.mIndexBuffer != VK_NULL_HANDLE) {
                vkDestroyBuffer(mDevice, meshComp.mIndexBuffer, nullptr);
                meshComp.mIndexBuffer = VK_NULL_HANDLE;
            }
            if (meshComp.mIndexBufferMemory != VK_NULL_HANDLE) {
                vkFreeMemory(mDevice, meshComp.mIndexBufferMemory, nullptr);
                meshComp.mIndexBufferMemory = VK_NULL_HANDLE;
            }
            continue;
        }

        // Add mesh component
        MeshComponent.push_back(meshComp);
        entity.addComponent(ComponentTypes::mesh, static_cast<short>(MeshComponent.size() - 1));

        // Add transform component
        transform transComp;
        transComp.mEntityId = entity.getEntityId();
        transComp.mPosition = glm::vec3(static_cast<float>(outEntities.size()) * 2.0f, 0.0f, 0.0f);
        TransformComponent.push_back(transComp);
        entity.addComponent(ComponentTypes::transform, static_cast<short>(TransformComponent.size() - 1));

        // Add texture component
        texture texComp;
        texComp.mEntityId = entity.getEntityId();
        texComp.mTextureImage = VK_NULL_HANDLE;
        texComp.mTextureImageMemory = VK_NULL_HANDLE;
        texComp.mTextureImageView = VK_NULL_HANDLE;
        texComp.mTextureSampler = VK_NULL_HANDLE;

        std::string texturePath = customTexturePath;
        if (texturePath.empty() && !shape.mesh.material_ids.empty() && shape.mesh.material_ids[0] >= 0 && static_cast<size_t>(shape.mesh.material_ids[0]) < materials.size()) {
            auto& mat = materials[shape.mesh.material_ids[0]];
            if (!mat.diffuse_texname.empty()) {
                texturePath = modelDir + mat.diffuse_texname;
            }
        }

        if (!texturePath.empty()) {
            bool texOk = true;
            try {
                createTextureImage(texturePath, texComp.mTextureImage, texComp.mTextureImageMemory);
            } catch (const std::exception& e) {
                qDebug() << "createTextureImage failed for shape" << (int)s << ":" << e.what();
                texOk = false;
            }

            if (texOk && texComp.mTextureImage != VK_NULL_HANDLE) {
                try {
                    createTextureImageView(texComp.mTextureImage, texComp.mTextureImageView);
                    createTextureSampler(texComp.mTextureSampler);
                } catch (const std::exception& e) {
                    qDebug() << "createTextureImageView/createTextureSampler failed for shape" << (int)s << ":" << e.what();
                    // Clean up partially created texture resources
                    if (texComp.mTextureImageView != VK_NULL_HANDLE) {
                        vkDestroyImageView(mDevice, texComp.mTextureImageView, nullptr);
                        texComp.mTextureImageView = VK_NULL_HANDLE;
                    }
                    if (texComp.mTextureSampler != VK_NULL_HANDLE) {
                        vkDestroySampler(mDevice, texComp.mTextureSampler, nullptr);
                        texComp.mTextureSampler = VK_NULL_HANDLE;
                    }
                }
            } else {
                qDebug() << "Texture skipped for shape" << (int)s;
            }
        }

        TextureComponent.push_back(texComp);
        entity.addComponent(ComponentTypes::texture, static_cast<short>(TextureComponent.size() - 1));

        outEntities.push_back(std::move(entity));
    } // shapes loop
}

void ModelLoader::createVertexBuffer(const std::vector<Vertex>& vertices, VkBuffer& buffer, VkDeviceMemory& memory)
{
    // If no vertices, set handles to null and return (avoid creating zero-size Vulkan buffers)
    if (vertices.empty()) {
        qDebug() << "createVertexBuffer: empty vertex array, skipping buffer creation.";
        buffer = VK_NULL_HANDLE;
        memory = VK_NULL_HANDLE;
        return;
    }

    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();
    if (bufferSize == 0) {
        qDebug() << "createVertexBuffer: computed bufferSize == 0, skipping.";
        buffer = VK_NULL_HANDLE;
        memory = VK_NULL_HANDLE;
        return;
    }

    qDebug() << "createVertexBuffer: bufferSize =" << static_cast<qulonglong>(bufferSize);

    VkBuffer stagingBuffer = VK_NULL_HANDLE;
    VkDeviceMemory stagingBufferMemory = VK_NULL_HANDLE;
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = bufferSize;
    bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(mDevice, &bufferInfo, nullptr, &stagingBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create staging buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(mDevice, stagingBuffer, &memRequirements);
    qDebug() << "createVertexBuffer: staging memRequirements.size =" << static_cast<qulonglong>(memRequirements.size);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if (vkAllocateMemory(mDevice, &allocInfo, nullptr, &stagingBufferMemory) != VK_SUCCESS) {
        vkDestroyBuffer(mDevice, stagingBuffer, nullptr);
        throw std::runtime_error("failed to allocate staging buffer memory!");
    }

    vkBindBufferMemory(mDevice, stagingBuffer, stagingBufferMemory, 0);

    void* data = nullptr;
    vkMapMemory(mDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
    vkUnmapMemory(mDevice, stagingBufferMemory);

    // Create device local vertex buffer
    bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    if (vkCreateBuffer(mDevice, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        vkDestroyBuffer(mDevice, stagingBuffer, nullptr);
        vkFreeMemory(mDevice, stagingBufferMemory, nullptr);
        throw std::runtime_error("failed to create vertex buffer!");
    }

    vkGetBufferMemoryRequirements(mDevice, buffer, &memRequirements);
    qDebug() << "createVertexBuffer: vertex memRequirements.size =" << static_cast<qulonglong>(memRequirements.size);
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    if (vkAllocateMemory(mDevice, &allocInfo, nullptr, &memory) != VK_SUCCESS) {
        vkDestroyBuffer(mDevice, buffer, nullptr);
        vkDestroyBuffer(mDevice, stagingBuffer, nullptr);
        vkFreeMemory(mDevice, stagingBufferMemory, nullptr);
        throw std::runtime_error("failed to allocate vertex buffer memory!");
    }

    vkBindBufferMemory(mDevice, buffer, memory, 0);
    copyBuffer(stagingBuffer, buffer, bufferSize);

    vkDestroyBuffer(mDevice, stagingBuffer, nullptr);
    vkFreeMemory(mDevice, stagingBufferMemory, nullptr);
}

void ModelLoader::createIndexBuffer(const std::vector<uint32_t>& indices, VkBuffer& buffer, VkDeviceMemory& memory)
{
    if (indices.empty()) {
        qDebug() << "createIndexBuffer: empty index array, skipping buffer creation.";
        buffer = VK_NULL_HANDLE;
        memory = VK_NULL_HANDLE;
        return;
    }

    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();
    if (bufferSize == 0) {
        qDebug() << "createIndexBuffer: computed bufferSize == 0, skipping.";
        buffer = VK_NULL_HANDLE;
        memory = VK_NULL_HANDLE;
        return;
    }

    qDebug() << "createIndexBuffer: bufferSize =" << static_cast<qulonglong>(bufferSize);

    VkBuffer stagingBuffer = VK_NULL_HANDLE;
    VkDeviceMemory stagingBufferMemory = VK_NULL_HANDLE;
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = bufferSize;
    bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(mDevice, &bufferInfo, nullptr, &stagingBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create staging buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(mDevice, stagingBuffer, &memRequirements);
    qDebug() << "createIndexBuffer: staging memRequirements.size =" << static_cast<qulonglong>(memRequirements.size);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if (vkAllocateMemory(mDevice, &allocInfo, nullptr, &stagingBufferMemory) != VK_SUCCESS) {
        vkDestroyBuffer(mDevice, stagingBuffer, nullptr);
        throw std::runtime_error("failed to allocate staging buffer memory!");
    }

    vkBindBufferMemory(mDevice, stagingBuffer, stagingBufferMemory, 0);

    void* data = nullptr;
    vkMapMemory(mDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), static_cast<size_t>(bufferSize));
    vkUnmapMemory(mDevice, stagingBufferMemory);

    bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    if (vkCreateBuffer(mDevice, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        vkDestroyBuffer(mDevice, stagingBuffer, nullptr);
        vkFreeMemory(mDevice, stagingBufferMemory, nullptr);
        throw std::runtime_error("failed to create index buffer!");
    }

    vkGetBufferMemoryRequirements(mDevice, buffer, &memRequirements);
    qDebug() << "createIndexBuffer: index memRequirements.size =" << static_cast<qulonglong>(memRequirements.size);
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    if (vkAllocateMemory(mDevice, &allocInfo, nullptr, &memory) != VK_SUCCESS) {
        vkDestroyBuffer(mDevice, buffer, nullptr);
        vkDestroyBuffer(mDevice, stagingBuffer, nullptr);
        vkFreeMemory(mDevice, stagingBufferMemory, nullptr);
        throw std::runtime_error("failed to allocate index buffer memory!");
    }

    vkBindBufferMemory(mDevice, buffer, memory, 0);
    copyBuffer(stagingBuffer, buffer, bufferSize);

    vkDestroyBuffer(mDevice, stagingBuffer, nullptr);
    vkFreeMemory(mDevice, stagingBufferMemory, nullptr);
}

void ModelLoader::createTextureImage(const std::string& path, VkImage& image, VkDeviceMemory& memory)
{
    image = VK_NULL_HANDLE;
    memory = VK_NULL_HANDLE;

    int texWidth = 0, texHeight = 0, texChannels = 0;
    stbi_uc* pixels = stbi_load(path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    if (!pixels || texWidth <= 0 || texHeight <= 0) {
        qDebug() << "createTextureImage: Failed to load texture or invalid dimensions for" << path.c_str();
        if (pixels) stbi_image_free(pixels);
        return;
    }

    VkDeviceSize imageSize = static_cast<VkDeviceSize>(texWidth) * static_cast<VkDeviceSize>(texHeight) * 4;
    if (imageSize == 0) {
        qDebug() << "createTextureImage: imageSize is zero, skipping texture for" << path.c_str();
        stbi_image_free(pixels);
        return;
    }

    qDebug() << "createTextureImage: imageSize =" << static_cast<qulonglong>(imageSize) << "for" << path.c_str();

    VkBuffer stagingBuffer = VK_NULL_HANDLE;
    VkDeviceMemory stagingBufferMemory = VK_NULL_HANDLE;
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = imageSize;
    bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(mDevice, &bufferInfo, nullptr, &stagingBuffer) != VK_SUCCESS) {
        stbi_image_free(pixels);
        throw std::runtime_error("failed to create staging buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(mDevice, stagingBuffer, &memRequirements);
    qDebug() << "createTextureImage: staging memRequirements.size =" << static_cast<qulonglong>(memRequirements.size);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if (vkAllocateMemory(mDevice, &allocInfo, nullptr, &stagingBufferMemory) != VK_SUCCESS) {
        vkDestroyBuffer(mDevice, stagingBuffer, nullptr);
        stbi_image_free(pixels);
        throw std::runtime_error("failed to allocate staging buffer memory!");
    }

    vkBindBufferMemory(mDevice, stagingBuffer, stagingBufferMemory, 0);

    void* data = nullptr;
    vkMapMemory(mDevice, stagingBufferMemory, 0, imageSize, 0, &data);
    memcpy(data, pixels, static_cast<size_t>(imageSize));
    vkUnmapMemory(mDevice, stagingBufferMemory);

    stbi_image_free(pixels);

    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = static_cast<uint32_t>(texWidth);
    imageInfo.extent.height = static_cast<uint32_t>(texHeight);
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;

    if (vkCreateImage(mDevice, &imageInfo, nullptr, &image) != VK_SUCCESS) {
        vkDestroyBuffer(mDevice, stagingBuffer, nullptr);
        vkFreeMemory(mDevice, stagingBufferMemory, nullptr);
        throw std::runtime_error("failed to create image!");
    }

    vkGetImageMemoryRequirements(mDevice, image, &memRequirements);
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    if (vkAllocateMemory(mDevice, &allocInfo, nullptr, &memory) != VK_SUCCESS) {
        vkDestroyImage(mDevice, image, nullptr);
        vkDestroyBuffer(mDevice, stagingBuffer, nullptr);
        vkFreeMemory(mDevice, stagingBufferMemory, nullptr);
        throw std::runtime_error("failed to allocate image memory!");
    }

    vkBindImageMemory(mDevice, image, memory, 0);
    transitionImageLayout(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    copyBufferToImage(stagingBuffer, image, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
    transitionImageLayout(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    vkDestroyBuffer(mDevice, stagingBuffer, nullptr);
    vkFreeMemory(mDevice, stagingBufferMemory, nullptr);
}

void ModelLoader::createTextureImageView(VkImage image, VkImageView& view)
{
    view = VK_NULL_HANDLE;
    if (image == VK_NULL_HANDLE) {
        qDebug() << "createTextureImageView: image is VK_NULL_HANDLE, skipping view creation.";
        return;
    }

    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    if (vkCreateImageView(mDevice, &viewInfo, nullptr, &view) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture image view!");
    }
}

void ModelLoader::createTextureSampler(VkSampler& sampler)
{
    sampler = VK_NULL_HANDLE;

    VkSamplerCreateInfo samplerInfo{};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.anisotropyEnable = VK_TRUE;
    VkPhysicalDeviceProperties properties{};
    vkGetPhysicalDeviceProperties(mPhysicalDevice, &properties);
    // Clamp to at least 1.0 in case the device reports 0
    float maxAniso = properties.limits.maxSamplerAnisotropy > 0.0f ? properties.limits.maxSamplerAnisotropy : 1.0f;
    samplerInfo.maxAnisotropy = maxAniso;
    samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    samplerInfo.mipLodBias = 0.0f;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 0.0f;

    if (vkCreateSampler(mDevice, &samplerInfo, nullptr, &sampler) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture sampler!");
    }
}

void ModelLoader::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
    if (srcBuffer == VK_NULL_HANDLE || dstBuffer == VK_NULL_HANDLE || size == 0) {
        qDebug() << "copyBuffer: invalid arguments, skipping copy";
        return;
    }

    VkCommandBuffer commandBuffer = beginSingleTimeCommands();

    VkBufferCopy copyRegion{};
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    endSingleTimeCommands(commandBuffer);
}

void ModelLoader::transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout)
{
    if (image == VK_NULL_HANDLE) {
        qDebug() << "transitionImageLayout: image is VK_NULL_HANDLE, skipping.";
        return;
    }

    VkCommandBuffer commandBuffer = beginSingleTimeCommands();

    VkImageMemoryBarrier barrier{};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout = oldLayout;
    barrier.newLayout = newLayout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;

    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;

    if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    } else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    } else {
        throw std::invalid_argument("unsupported layout transition!");
    }

    vkCmdPipelineBarrier(
        commandBuffer,
        sourceStage, destinationStage,
        0,
        0, nullptr,
        0, nullptr,
        1, &barrier
        );

    endSingleTimeCommands(commandBuffer);
}

void ModelLoader::copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
{
    if (buffer == VK_NULL_HANDLE || image == VK_NULL_HANDLE || width == 0 || height == 0) {
        qDebug() << "copyBufferToImage: invalid arguments, skipping.";
        return;
    }

    VkCommandBuffer commandBuffer = beginSingleTimeCommands();

    VkBufferImageCopy region{};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;
    region.imageOffset = {0, 0, 0};
    region.imageExtent = {width, height, 1};

    vkCmdCopyBufferToImage(
        commandBuffer,
        buffer,
        image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        1,
        &region
        );

    endSingleTimeCommands(commandBuffer);
}

VkCommandBuffer ModelLoader::beginSingleTimeCommands()
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = mCommandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer = VK_NULL_HANDLE;
    vkAllocateCommandBuffers(mDevice, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);
    return commandBuffer;
}

void ModelLoader::endSingleTimeCommands(VkCommandBuffer commandBuffer)
{
    if (commandBuffer == VK_NULL_HANDLE) return;

    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(mGraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(mGraphicsQueue);

    vkFreeCommandBuffers(mDevice, mCommandPool, 1, &commandBuffer);
}

uint32_t ModelLoader::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(mPhysicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}

} // namespace bbl
