#pragma once

#include "component.h"

class Mesh : public Component
{
private:

public:
    Mesh(const char* filePath,
         const char* vertexShaderPath = "shaders/phong.vert.spv",
         const char* fragmentShaderPath = "shaders/phong.frag.spv");
    void Update();

    Renderer::Drawable* drawable;
};
