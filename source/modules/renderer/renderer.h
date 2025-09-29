#pragma once

#include "vertex.h" // TODO: Figure out if vulkan can be decoupled from vertex.h

class Renderer
{
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
public:
    class Drawable
    {
    public:
        struct UniformBufferObject {
            alignas(16) glm::mat4 model;
            alignas(16) glm::mat4 view;
            alignas(16) glm::mat4 proj;
            alignas(16) glm::mat4 modelMat;
            alignas(16) glm::mat4 normalMat;
            alignas(16) glm::vec3 lightPosition;
            alignas(16) glm::vec3 cameraPosition;
            alignas(16) glm::float32_t time;
        } ubo;

        VkPipeline graphicsPipeline;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;

        int indicesQuantity  = 0;
        int verticesQuantity = 0;

        bool isVisible = true;

        int offset = 0;
    };

    virtual Drawable& CreateDrawable(std::vector<Vertex> vertices,
                                     std::vector<uint32_t> indices = std::vector<uint32_t>(),
                                     const char* vertexShader = "shaders/vert.spv",
                                     const char* fragmentShader = "shaders/frag.spv") = 0;

    virtual void SetViewMatrix(glm::mat4 view) = 0;
    virtual void SetCameraPosition(glm::vec3 pos) = 0;
    virtual void SetLightPos(glm::vec3 pos) = 0;
};
