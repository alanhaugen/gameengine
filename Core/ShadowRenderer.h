#ifndef SHADOWRENDERER_H
#define SHADOWRENDERER_H

#include "Core/Engine.h"
#include <vulkan/vulkan.h>
#include "Vertex.h"
#include "VulkanHelper.h"

class ShadowRenderer
{
public:
    ShadowRenderer(VkDevice vulkanDevice, VkDescriptorSet set, VkDescriptorSetLayout setLayout);

	VkDevice mDevice;
    VkRenderPass shadowRenderPass;
    VkFramebuffer shadowFramebuffer;
    VkImage shadowMapImage;
    VkImageView shadowMapImageView;
    VkSampler shadowMapSampler;
    VkPipelineLayout shadowPipelineLayout;
    VkPipeline shadowPipeline;
    VkDeviceMemory shadowMapMemory;
    uint32_t shadowMapWidth = 1024;
    uint32_t shadowMapHeight = 1024;

	VkDescriptorSetLayout lightDescriptorSetLayout;
	VkDescriptorSet lightDescriptorSet;

    void CreateImage();
    void CreateImageView();
	void CreateSampler();
    void CreateRenderPass();
    void CreateFrameBuffer();
    void CreatePipeline();
#
	void Initialize();
    void Cleanup();
    void RecordCommandBuffer(std::vector<gea::RenderComponent> renderComponents, std::vector<gea::TransformComponent> transformComponents, std::vector<gea::Mesh> meshes, VkCommandBuffer& shadowCommandBuffer);
};

#endif // SHADOWRENDERER_H
