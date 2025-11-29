#pragma once

#include "../renderer.h"
#include <vector>

class NullRenderer : public Renderer
{
public:
    void Init();
    void Update();

    int CreateDrawable(std::vector<Vertex> vertices,
                             std::vector<uint32_t> indices,
                             const char* vertexShader = "shaders/vert.spv",
                             const char* fragmentShader = "shaders/frag.spv",
                             const int topology = TRIANGLES,
                             const char* texture = "",
                             const bool depthTesting = true,
                             const bool isInstanced = false);

    void RemoveDrawable(int index);

    void SetModel(int index, glm::mat4 model);
    void SetColour(int index, glm::vec4 colour);
    void SetPosition(int index, glm::vec3 pos);
    glm::vec3 GetPosition(int index);
    void Scale(int index, glm::vec3 scale);
    void Rotate(int index, float angle, glm::vec3 axis);
    void Translate(int index, glm::vec3 translation);
    void Show(int index);
    void Hide(int index);
    void SetWidth(int index, float width);
    float GetWidth(int index);
    void SetHeight(int index, float height);
    float GetHeight(int index);
    void SetTotalTextureWidth(int index, float textureWidth);
    float GetTotalTextureWidth(int index);
    void SetTotalTextureHeight(int index, float textureHeight);
    float GetTotalTextureHeight(int index);
    void SetTextureWidth(int index, float textureWidth);
    float GetTextureWidth(int index);
    void SetTextureHeight(int index, float textureHeight);
    float GetTextureHeight(int index);
    void SetScaleX(int index, float scaleX);
    float GetScaleX(int index);
    void SetScaleY(int index, float scaleY);
    float GetScaleY(int index);
    void SetFlipX(int index, float flipX);
    float GetFlipX(int index);
    void SetFlipY(int index, float flipY);
    float GetFlipY(int index);
    void SetSpriteSheetFrameIndex(int drawable, float index);
    int GetSpriteSheetFrameIndex(int drawable);
    bool isVisible(int index);

    void SetViewMatrix(glm::mat4 view);
    void SetCameraPosition(glm::vec3 pos);
    void SetLightPos(glm::vec3 pos);
    glm::mat4 GetProjectionMatrix();
};
