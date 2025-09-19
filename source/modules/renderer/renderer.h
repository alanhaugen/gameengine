#pragma once

#include "vertex.h" // TODO: Figure out if vulkan can be decoupled from vertex.h

class Renderer
{
public:
    class Drawable
    {
    public:
        struct UniformBufferObject {
            alignas(16) glm::mat4 model;
            alignas(16) glm::mat4 view;
            alignas(16) glm::mat4 proj;
        } ubo;

        VkPipeline graphicsPipeline;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;

        int indicesQuantity  = 0;
        int verticesQuantity = 0;

        bool isVisible = true;

        VkDeviceSize offset = 0;
    };

    virtual Drawable& CreateDrawable(std::vector<Vertex> vertices,
                                    std::vector<uint32_t> indices,
                                    const char* vertexShader = "../../shaders/vert.spv",
                                    const char* fragmentShader = "../../shaders/frag.spv") = 0;
};
