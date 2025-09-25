#include "nullrenderer.h"

void NullRenderer::Init()
{
}

void NullRenderer::Update()
{
}

Renderer::Drawable &NullRenderer::CreateDrawable(std::vector<Vertex> vertices, std::vector<uint32_t> indices, const char *vertexShader, const char *fragmentShader)
{
    Drawable drawable;
    drawables.push_back(drawable);
    return drawables.back();
}
