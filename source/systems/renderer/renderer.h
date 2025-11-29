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
        int id;

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
        bool isInstanced = false;

        std::string textureFilePath;
        int textureId;

        int offset = 0;
        int instanceCount = 1;
        int instanceOffset;

        float textureWidth = 0.0f;
        float textureHeight = 0.0f;
    };

    float windowWidth, windowHeight;

    virtual int CreateDrawable(std::vector<Vertex> vertices,
                                     std::vector<uint32_t> indices = std::vector<uint32_t>(),
                                     const char* vertexShader = "shaders/vert.spv",
                                     const char* fragmentShader = "shaders/frag.spv",
                                     const int topology = TRIANGLES,
                                     const char* texture = "",
                                     const bool depthTesting = true,
                                     const bool isInstanced = false) = 0;

    virtual void RemoveDrawable(int index) = 0;

    virtual void SetModel(int drawable, glm::mat4 model) = 0;
    virtual void SetColour(int drawable, glm::vec4 colour) = 0;
    virtual void SetPosition(int drawable, glm::vec3 pos) = 0;
    virtual glm::vec3 GetPosition(int drawable) = 0;
    virtual void Scale(int drawable, glm::vec3 scale) = 0;
    virtual void Rotate(int drawable, float angle, glm::vec3 axis) = 0;
    virtual void Translate(int drawable, glm::vec3 translation) = 0;
    virtual void Show(int drawable) = 0;
    virtual void Hide(int drawable) = 0;
    virtual void SetWidth(int drawable, float width) = 0;
    virtual float GetWidth(int drawable) = 0;
    virtual void SetHeight(int drawable, float height) = 0;
    virtual float GetHeight(int drawable) = 0;
    virtual void SetTotalTextureWidth(int drawable, float textureWidth) = 0;
    virtual float GetTotalTextureWidth(int drawable) = 0;
    virtual void SetTotalTextureHeight(int drawable, float textureHeight) = 0;
    virtual float GetTotalTextureHeight(int drawable) = 0;
    virtual void SetTextureWidth(int drawable, float textureWidth) = 0;
    virtual float GetTextureWidth(int drawable) = 0;
    virtual void SetTextureHeight(int drawable, float textureHeight) = 0;
    virtual float GetTextureHeight(int drawable) = 0;
    virtual void SetScaleX(int drawable, float scaleX) = 0;
    virtual float GetScaleX(int drawable) = 0;
    virtual void SetScaleY(int drawable, float scaleY) = 0;
    virtual float GetScaleY(int drawable) = 0;
    virtual void SetFlipX(int drawable, float flipX) = 0;
    virtual float GetFlipX(int drawable) = 0;
    virtual void SetFlipY(int drawable, float flipY) = 0;
    virtual float GetFlipY(int drawable) = 0;
    virtual void SetSpriteSheetFrameIndex(int drawable, float index) = 0;
    virtual int GetSpriteSheetFrameIndex(int drawable) = 0;
    virtual bool isVisible(int drawable) = 0;

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
