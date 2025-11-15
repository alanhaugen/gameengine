#include "nullrenderer.h"

void NullRenderer::Init()
{
}

void NullRenderer::Update()
{
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

Renderer::Drawable &NullRenderer::CreateDrawable(std::vector<Vertex> vertices,
                                                 std::vector<uint32_t> indices,
                                                 const char *vertexShader,
                                                 const char *fragmentShader,
                                                 const int topology,
                                                 const char* texture,
                                                 const bool depthTesting)
{
    Drawable drawable;
    drawables.push_back(drawable);
    return drawables.back();
}
