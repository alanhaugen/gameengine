#pragma once

#include "component.h"
#include "../modules/renderer/renderer.h"
#include "../x-platform/editor.h"

class Mesh : public Component
{
private:

public:
    Mesh(const char* filePath,
         Renderer* renderer,
         Editor* editor = nullptr,
         const char* vertexShaderPath = "shaders/shader.vert.spv",
         const char* fragmentShaderPath = "shaders/shader.frag.spv");
    void Update();

    Renderer::Drawable* drawable;

    void SetName(const QString NewName);


    const QString GetName();



};
