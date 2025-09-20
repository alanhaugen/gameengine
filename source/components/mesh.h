#pragma once

#include "component.h"
#include "../modules/renderer/renderer.h"

class Mesh : public Component
{
private:

public:
    Mesh(const char* filePath,
         Renderer* renderer,
         const char* vertexShaderPath = "../../shaders/vert.spv",
         const char* fragmentShaderPath = "../../shaders/frag.spv");
    void Update();

    Renderer::Drawable* drawable;
};
