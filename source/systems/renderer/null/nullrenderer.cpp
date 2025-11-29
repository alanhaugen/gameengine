#include "nullrenderer.h"

void NullRenderer::Init()
{
}

void NullRenderer::Update()
{
}

void NullRenderer::RemoveDrawable(int index)
{
}

void NullRenderer::SetModel(int index, glm::mat4 model)
{
}

void NullRenderer::SetColour(int index, glm::vec4 colour)
{
}

void NullRenderer::SetPosition(int index, glm::vec3 pos)
{
}

glm::vec3 NullRenderer::GetPosition(int index)
{
    return glm::vec3();
}

void NullRenderer::Scale(int index, glm::vec3 scale)
{
}

void NullRenderer::Rotate(int index, float angle, glm::vec3 axis)
{
}

void NullRenderer::Translate(int index, glm::vec3 translation)
{
}

void NullRenderer::Show(int index)
{
}

void NullRenderer::Hide(int index)
{
}

void NullRenderer::SetWidth(int index, float width)
{

}

float NullRenderer::GetWidth(int index)
{
    return 0.0f;
}

void NullRenderer::SetHeight(int index, float height)
{
}

float NullRenderer::GetHeight(int index)
{
    return 0.0f;
}

void NullRenderer::SetTotalTextureWidth(int index, float textureWidth)
{
}

float NullRenderer::GetTotalTextureWidth(int index)
{
    return 0.0f;
}

void NullRenderer::SetTotalTextureHeight(int index, float textureHeight)
{
}

float NullRenderer::GetTotalTextureHeight(int index)
{
    return 0.0f;
}

void NullRenderer::SetTextureWidth(int index, float textureWidth)
{
}

float NullRenderer::GetTextureWidth(int index)
{
    return 0.0f;
}

void NullRenderer::SetTextureHeight(int index, float textureHeight)
{
}

float NullRenderer::GetTextureHeight(int index)
{
    return 0.0f;
}

void NullRenderer::SetScaleX(int index, float scaleX)
{
}

float NullRenderer::GetScaleX(int index)
{
    return 0.0f;
}

void NullRenderer::SetScaleY(int index, float scaleY)
{
}

float NullRenderer::GetScaleY(int index)
{
    return 0.0f;
}

void NullRenderer::SetFlipX(int index, float flipX)
{
}

float NullRenderer::GetFlipX(int index)
{
    return 0.0f;
}

void NullRenderer::SetFlipY(int index, float flipY)
{
}

float NullRenderer::GetFlipY(int index)
{
    return 0.0f;
}

void NullRenderer::SetSpriteSheetFrameIndex(int drawable, float index)
{
}

int NullRenderer::GetSpriteSheetFrameIndex(int drawable)
{
    return 0;
}

bool NullRenderer::isVisible(int index)
{
    return false;
}

void NullRenderer::SetViewMatrix(glm::mat4 view)
{
}

void NullRenderer::SetCameraPosition(glm::vec3 pos)
{
}

void NullRenderer::SetLightPos(glm::vec3 pos)
{
}

glm::mat4 NullRenderer::GetProjectionMatrix()
{
    return glm::mat4();
}

int NullRenderer::CreateDrawable(std::vector<Vertex> vertices,
                                 std::vector<uint32_t> indices,
                                 const char *vertexShader,
                                 const char *fragmentShader,
                                 const int topology,
                                 const char* texture,
                                 const bool depthTesting,
                                 const bool isInstanced)
{
    return -1;
}
