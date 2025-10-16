#include "ShadowRenderer.h"
#include <stdexcept>

ShadowRenderer::ShadowRenderer(VkDevice vulkanDevice, VkDescriptorSet set, VkDescriptorSetLayout setLayout)
{
	mDevice = vulkanDevice;
	lightDescriptorSet = set;
	lightDescriptorSetLayout = setLayout;
}

void ShadowRenderer::Cleanup()
{
	vkDestroySampler(mDevice, shadowMapSampler, nullptr);
	vkDestroyImageView(mDevice, shadowMapImageView, nullptr);
	vkDestroyImage(mDevice, shadowMapImage, nullptr);
	vkFreeMemory(mDevice, shadowMapMemory, nullptr);

	vkDestroyPipeline(mDevice, shadowPipeline, nullptr);
	vkDestroyPipelineLayout(mDevice, shadowPipelineLayout, nullptr);
	vkDestroyRenderPass(mDevice, shadowRenderPass, nullptr);
}

void ShadowRenderer::CreateImage()
{
	VkImageCreateInfo imageCreateInfo{};
	imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
	imageCreateInfo.format = VK_FORMAT_D32_SFLOAT;
	imageCreateInfo.extent.width = shadowMapWidth;
	imageCreateInfo.extent.height = shadowMapHeight;
	imageCreateInfo.extent.depth = 1;
	imageCreateInfo.mipLevels = 1;
	imageCreateInfo.arrayLayers = 1;
	imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
	imageCreateInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	vkCreateImage(mDevice, &imageCreateInfo, nullptr, &shadowMapImage);
}

void ShadowRenderer::CreateImageView()
{
	VkMemoryRequirements memReq;
	vkGetImageMemoryRequirements(mDevice, shadowMapImage, &memReq);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memReq.size;
	allocInfo.memoryTypeIndex = VulkanHelper::FindMemoryType(memReq.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	vkAllocateMemory(mDevice, &allocInfo, nullptr, &shadowMapMemory);
	vkBindImageMemory(mDevice, shadowMapImage, shadowMapMemory, 0);

	VkImageViewCreateInfo viewInfo{};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = shadowMapImage;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = VK_FORMAT_D32_SFLOAT;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.layerCount = 1;
	vkCreateImageView(mDevice, &viewInfo, nullptr, &shadowMapImageView);
}

void ShadowRenderer::CreateSampler()
{
	VkSamplerCreateInfo shadowMapSamplerInfo{};
	shadowMapSamplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	shadowMapSamplerInfo.magFilter = VK_FILTER_LINEAR;
	shadowMapSamplerInfo.minFilter = VK_FILTER_LINEAR;
	shadowMapSamplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
	shadowMapSamplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
	shadowMapSamplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
	shadowMapSamplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
	shadowMapSamplerInfo.unnormalizedCoordinates = VK_FALSE;
	shadowMapSamplerInfo.anisotropyEnable = VK_FALSE;
	shadowMapSamplerInfo.maxAnisotropy = 1.0f;
	shadowMapSamplerInfo.compareEnable = VK_TRUE;
	shadowMapSamplerInfo.compareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
	shadowMapSamplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	shadowMapSamplerInfo.minLod = 0.0f;
	shadowMapSamplerInfo.maxLod = 1.0f;
	shadowMapSamplerInfo.mipLodBias = 0.0f;
	vkCreateSampler(mDevice, &shadowMapSamplerInfo, nullptr, &shadowMapSampler);
}

void ShadowRenderer::CreateRenderPass()
{
	VkAttachmentDescription depthAtt = {};
	depthAtt.format = VK_FORMAT_D32_SFLOAT;
	depthAtt.samples = VK_SAMPLE_COUNT_1_BIT;
	depthAtt.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	depthAtt.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	depthAtt.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	depthAtt.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	depthAtt.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	depthAtt.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentReference depthAttRef = {};
	depthAttRef.attachment = 0;
	depthAttRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 0;
	subpass.pDepthStencilAttachment = &depthAttRef;
	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	dependency.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
	dependency.dstStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	dependency.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &depthAtt;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;
	vkCreateRenderPass(mDevice, &renderPassInfo, nullptr, &shadowRenderPass);
}

void ShadowRenderer::CreateFrameBuffer()
{
	VkFramebufferCreateInfo framebufferInfo{};
	framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebufferInfo.renderPass = shadowRenderPass;
	framebufferInfo.attachmentCount = 1;
	framebufferInfo.pAttachments = &shadowMapImageView;
	framebufferInfo.width = shadowMapWidth;
	framebufferInfo.height = shadowMapHeight;
	framebufferInfo.layers = 1;
	vkCreateFramebuffer(mDevice, &framebufferInfo, nullptr, &shadowFramebuffer);
}

void ShadowRenderer::CreatePipeline()
{
	VkPushConstantRange pushConstantRange{};
	pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	pushConstantRange.offset = 0;
	pushConstantRange.size = sizeof(glm::mat4);

	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 1;
	pipelineLayoutInfo.pSetLayouts = &lightDescriptorSetLayout;
	pipelineLayoutInfo.pushConstantRangeCount = 1;
	pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

	if (vkCreatePipelineLayout(mDevice, &pipelineLayoutInfo, nullptr, &shadowPipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create pipeline layout!");
	}

	//create shader stages for shadow map
	auto vertShaderCode = VulkanHelper::ReadFile(PATH + "Shaders/ShadowMap.vert.spv");
	auto fragShaderCode = VulkanHelper::ReadFile(PATH + "Shaders/ShadowMap.frag.spv");
	VkShaderModule vertShaderModule = VulkanHelper::CreateShaderModule(vertShaderCode);
	VkShaderModule fragShaderModule = VulkanHelper::CreateShaderModule(fragShaderCode);
	VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertShaderStageInfo.module = vertShaderModule;
	vertShaderStageInfo.pName = "main";
	VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = fragShaderModule;
	fragShaderStageInfo.pName = "main";
	VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

	//create fixed functions for shadow map
	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	auto bindingDescription = Vertex::getBindingDescription();
	auto attributeDescriptions = Vertex::getAttributeDescriptions();
	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
	vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
	vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
	VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;
	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)shadowMapWidth;
	viewport.height = (float)shadowMapHeight;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = { shadowMapWidth, shadowMapHeight };
	VkPipelineViewportStateCreateInfo viewportState{};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;
	VkPipelineRasterizationStateCreateInfo rasterizer{};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	//todo (insert if "shadow acne" whatever this is)
	//rasterizer.depthBiasEnable = VK_TRUE;
	//rasterizer.depthBiasConstantFactor = 1.25f;
	//rasterizer.depthBiasSlopeFactor = 1.75f;
	rasterizer.depthBiasEnable = VK_FALSE;
	rasterizer.depthBiasConstantFactor = 0.0f;
	rasterizer.depthBiasClamp = 0.0f;
	rasterizer.depthBiasSlopeFactor = 0.0f;
	VkPipelineMultisampleStateCreateInfo multisampling{};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	VkPipelineDepthStencilStateCreateInfo depthStencil{};
	depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencil.depthTestEnable = VK_TRUE;
	depthStencil.depthWriteEnable = VK_TRUE;
	depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
	depthStencil.depthBoundsTestEnable = VK_FALSE;
	depthStencil.minDepthBounds = 0.0f;
	depthStencil.maxDepthBounds = 1.0f;
	depthStencil.stencilTestEnable = VK_FALSE;
	depthStencil.front = {};
	depthStencil.back = {};
	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;
	VkPipelineColorBlendStateCreateInfo colorBlending{};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;

	//create pipeline for shadow map
	VkGraphicsPipelineCreateInfo pipelineInfo{};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pDepthStencilState = &depthStencil;
	pipelineInfo.layout = shadowPipelineLayout;
	pipelineInfo.renderPass = shadowRenderPass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

	//Create Graphics Pipeline
	if (vkCreateGraphicsPipelines(mDevice, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &shadowPipeline) != VK_SUCCESS)
		throw std::runtime_error("failed to create graphics pipeline!");
}

void ShadowRenderer::Initialize()
{
	CreateImage();
	CreateImageView();
	CreateSampler();
	CreateRenderPass();
	CreateFrameBuffer();
	CreatePipeline();

	//put back into renderer


	
}

void ShadowRenderer::RecordCommandBuffer(std::vector<gea::RenderComponent> renderComponents, std::vector<gea::TransformComponent> transformComponents, std::vector<gea::Mesh> meshes, VkCommandBuffer& shadowCommandBuffer)
{
	VkCommandBufferBeginInfo shadowBeginInfo{};
	shadowBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	shadowBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	VkRenderPassBeginInfo shadowRenderPassBeginInfo{};
	shadowRenderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	shadowRenderPassBeginInfo.renderPass = shadowRenderPass;
	shadowRenderPassBeginInfo.framebuffer = shadowFramebuffer;
	shadowRenderPassBeginInfo.renderArea.offset = { 0, 0 };
	shadowRenderPassBeginInfo.renderArea.extent = { shadowMapWidth , shadowMapWidth };
	shadowRenderPassBeginInfo.clearValueCount = 1;
	VkClearValue clearValue{};
	clearValue.depthStencil = { 1.0f, 0 };
	shadowRenderPassBeginInfo.pClearValues = &clearValue;

	vkBeginCommandBuffer(shadowCommandBuffer, &shadowBeginInfo);
	vkCmdBeginRenderPass(shadowCommandBuffer, &shadowRenderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
	vkCmdBindPipeline(shadowCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, shadowPipeline);
	for (size_t j = 0; j < renderComponents.size(); j++)
	{
		gea::RenderComponent renderComponent = renderComponents[j];
		gea::Mesh mesh = meshes[renderComponent.meshIndex];
		VkBuffer vertexBuffer = mesh.mVertexBuffer;
		VkBuffer indexBuffer = mesh.mIndexBuffer;
		std::vector<uint32_t> indices = mesh.mIndices;
		VkDeviceSize offsets[] = { 0 };

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, transformComponents[j].mPosition);
		model = glm::rotate(model, glm::radians(transformComponents[j].mRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(transformComponents[j].mRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(transformComponents[j].mRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, transformComponents[j].mScale);

		vkCmdPushConstants(shadowCommandBuffer, shadowPipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(glm::mat4), &model);

		vkCmdBindVertexBuffers(shadowCommandBuffer, 0, 1, &vertexBuffer, offsets);
		vkCmdBindIndexBuffer(shadowCommandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);
		vkCmdBindDescriptorSets(shadowCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, shadowPipelineLayout, 0, 1, &lightDescriptorSet, 0, nullptr);
		vkCmdDrawIndexed(shadowCommandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
	}
	vkCmdEndRenderPass(shadowCommandBuffer);

	VkImageMemoryBarrier barrier{};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	barrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
	barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
	barrier.image = shadowMapImage;
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.layerCount = 1;

	vkCmdPipelineBarrier(
		shadowCommandBuffer,
		VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
		VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
		0,
		0, nullptr, 0, nullptr,
		1, &barrier
	);

	vkEndCommandBuffer(shadowCommandBuffer);
}