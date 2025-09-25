#pragma once

#include "../renderer.h"
#include <vector>

class NullRenderer : public Renderer
{
private:
    std::vector<Drawable> drawables;

public:
    void Init();
    void Update();

    Drawable& CreateDrawable(std::vector<Vertex> vertices,
                             std::vector<uint32_t> indices,
                             const char* vertexShader = "shaders/vert.spv",
                             const char* fragmentShader = "shaders/frag.spv");
};
