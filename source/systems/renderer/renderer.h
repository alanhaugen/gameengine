#pragma once

#include "vertex.h" // TODO: Figure out if vulkan can be decoupled from vertex.h
#include <string>

class Renderer
{
public:
    virtual void Init() = 0;
    virtual void Update() = 0;

public:
    enum Topology
    {
        TRIANGLES,
        LINES,
        LINES_STRIP,
        POINTS
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
            alignas(16) glm::vec4 lightPosition;
            alignas(16) glm::vec4 cameraPosition;
            alignas(16) glm::vec4 time;
            alignas(16) glm::vec4 index;
            alignas(16) glm::vec4 pos;
            alignas(16) glm::vec4 scaleX;
            alignas(16) glm::vec4 scaleY;
            alignas(16) glm::vec4 width;
            alignas(16) glm::vec4 height;
            alignas(16) glm::vec4 totalWidth;
            alignas(16) glm::vec4 totalHeight;
            alignas(16) glm::vec4 screenWidth;
            alignas(16) glm::vec4 screenHeight;
            alignas(16) glm::vec4 flip;
            alignas(16) glm::vec4 flipVertical;
            alignas(16) glm::vec4 colour;
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

        std::string textureFilePath;
        int textureId;

        int offset = 0;

        float textureWidth = 0.0f;
        float textureHeight = 0.0f;
    };

    float windowWidth, windowHeight;

    virtual Drawable& CreateDrawable(std::vector<Vertex> vertices,
                                     std::vector<uint32_t> indices = std::vector<uint32_t>(),
                                     const char* vertexShader = "shaders/vert.spv",
                                     const char* fragmentShader = "shaders/frag.spv",
                                     const int topology = TRIANGLES,
                                     const char* texture = "",
                                     const bool depthTesting = true) = 0;

    virtual void SetViewMatrix(glm::mat4 view) = 0;
    virtual void SetCameraPosition(glm::vec3 pos) = 0;
    virtual void SetLightPos(glm::vec3 pos) = 0;

    glm::mat4 cameraView;
    virtual glm::mat4 GetProjectionMatrix() = 0;
    float clearColor[4] = {0.0f, 0.3f, 0.5f, 1.0f};

    inline void SetClearColor(float r, float g, float b) {
        clearColor[0] = r;
        clearColor[1] = g;
        clearColor[2] = b;
    }
};
