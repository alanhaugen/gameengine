#pragma once

#include "component.h"

class Terrain : public Component
{
private:

public:
    Terrain(const char* filePath,
         const char* vertexShaderPath = "shaders/shader.vert.spv",
         const char* fragmentShaderPath = "shaders/shader.frag.spv");
    void Update();

    Renderer::Drawable* drawable;
};
