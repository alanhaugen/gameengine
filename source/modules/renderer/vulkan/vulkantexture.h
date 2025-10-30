#ifndef VULKANTEXTURE_H
#define VULKANTEXTURE_H

#include <vulkan/vulkan_core.h>

struct VulkanTexture
{
    uint32_t mipLevels;
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;

    int width;
    int height;
};

#endif // VULKANTEXTURE_H
