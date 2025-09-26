#pragma once

#include "component.h"

class Terrain : public Component
{
private:

public:
    Terrain(const char* filePath,
         const char* vertexShaderPath = "shaders/phong.vert.spv",
         const char* fragmentShaderPath = "shaders/phong.frag.spv");
    void Update();

    Renderer::Drawable* drawable;
};
