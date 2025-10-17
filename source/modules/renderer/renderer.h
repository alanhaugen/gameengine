#pragma once

#include "vertex.h" // TODO: Figure out if vulkan can be decoupled from vertex.h

class Renderer
{
public:
    virtual void Init() = 0;
    virtual void Update() = 0;

public:
    enum Topology
    {
        TRIANGLES,
        LINES
    };

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
            alignas(16) glm::float32_t index;
            alignas(16) glm::float32_t pos;
            alignas(16) glm::float32_t scaleX;
            alignas(16) glm::float32_t scaleY;
            alignas(16) glm::float32_t width;
            alignas(16) glm::float32_t height;
            alignas(16) glm::float32_t totalWidth;
            alignas(16) glm::float32_t totalHeight;
            alignas(16) glm::float32_t screenWidth;
            alignas(16) glm::float32_t screenHeight;
            alignas(16) glm::bvec1 flip;
            alignas(16) glm::bvec1 flipVertical;
        } ubo;

        VkPipeline graphicsPipeline;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;
        VkDescriptorSet textureDescriptor{};

        int indicesQuantity  = 0;
        int verticesQuantity = 0;

        bool isVisible  = true;
        bool isTextured = false;

        int offset = 0;
    };

    float windowWidth, windowHeight;

    virtual Drawable& CreateDrawable(std::vector<Vertex> vertices,
                                     std::vector<uint32_t> indices = std::vector<uint32_t>(),
                                     const char* vertexShader = "shaders/vert.spv",
                                     const char* fragmentShader = "shaders/frag.spv",
                                     const int topology = TRIANGLES,
                                     const char* texture = "") = 0;

    virtual void SetViewMatrix(glm::mat4 view) = 0;
    virtual void SetCameraPosition(glm::vec3 pos) = 0;
    virtual void SetLightPos(glm::vec3 pos) = 0;
};
