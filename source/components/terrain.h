#pragma once

#include "component.h"

class Terrain : public Component
{
private:

public:
    Terrain(const char* filePath,
         const char* vertexShaderPath = "shaders/color.vert.spv",
         const char* fragmentShaderPath = "shaders/color.frag.spv");
    void Update();

    Renderer::Drawable* drawable;
};
