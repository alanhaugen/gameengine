#ifndef VULKANHELPER_H
#define VULKANHELPER_H

#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <fstream>

class VulkanHelper
{
public:
    static void Init(VkDevice device, VkPhysicalDevice physicalDevice)
    {
        sDevice = device;
		sPhysicalDevice = physicalDevice;
    }
    static VkShaderModule CreateShaderModule(const std::vector<char>& code);
    static std::vector<char> ReadFile(const std::string& filename);
    static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
private:
    static VkDevice sDevice;
    static VkPhysicalDevice sPhysicalDevice;
};

#endif // VULKANHELPER_H
