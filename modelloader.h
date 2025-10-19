#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include "Components.h"
#include <string>
#include <vulkan/vulkan.h>
#include <vector>
#include "Entity.h"

namespace bbl
{
class ModelLoader
{
public:
    ModelLoader(VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue);
    void loadModel(const std::string& modelPath, std::vector<Entity>& outEntities, const std::string& customTexturePath = "");


    void createVertexBuffer(const std::vector<Vertex>& vertices, VkBuffer& buffer, VkDeviceMemory& memory);
    void createIndexBuffer(const std::vector<uint32_t>& indices, VkBuffer& buffer, VkDeviceMemory& memory);

private:
    VkDevice mDevice;
    VkPhysicalDevice mPhysicalDevice;
    VkCommandPool mCommandPool;
    VkQueue mGraphicsQueue;


    void createTextureImage(const std::string& path, VkImage& image, VkDeviceMemory& memory);
    void createTextureImageView(VkImage image, VkImageView& view);
    void createTextureSampler(VkSampler& sampler);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};
}

#endif // MODEL_LOADER_H
