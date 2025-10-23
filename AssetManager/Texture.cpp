#include "Texture.h"

gea::Texture::Texture()
{
	mMipLevels = 1;
	mTextureImage = VK_NULL_HANDLE;
	mTextureImageMemory = VK_NULL_HANDLE;
	mTextureImageView = VK_NULL_HANDLE;
	mTextureSampler = VK_NULL_HANDLE;
}

void gea::Texture::createTextureImage(QString MODEL_PATH)
{

        // stbi_uc* pixels = stbi_load(MODEL_PATH.toStdString().c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
        // //VkDeviceSize imageSize = texWidth * texHeight * 4;
        // mMipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;

        // if (!pixels) {
        //     throw std::runtime_error("failed to load texture image!");
        // }

        // // VkBuffer stagingBuffer;
        // // VkDeviceMemory stagingBufferMemory;
        // // createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        // // void* data;
        // // vkMapMemory(device, stagingBufferMemory, 0, imageSize, 0, &data);
        // // memcpy(data, pixels, static_cast<size_t>(imageSize));
        // // vkUnmapMemory(device, stagingBufferMemory);

        // stbi_image_free(pixels);

        // createImage(texWidth, texHeight, mMipLevels, VK_SAMPLE_COUNT_1_BIT, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, mTextureImage, mTextureImageMemory);

        // transitionImageLayout(mTextureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, texture->mMipLevels);
        // //copyBufferToImage(stagingBuffer,mTextureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
        // ////transitioned to VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL while generating mipmaps

        // // vkDestroyBuffer(device, stagingBuffer, nullptr);
        // // vkFreeMemory(device, stagingBufferMemory, nullptr);

        // generateMipmaps(mTextureImage, VK_FORMAT_R8G8B8A8_SRGB, texWidth, texHeight, mMipLevels);

        // createTextureImageView();
        // createTextureSampler();

}
