#pragma once

#include "component.h"

class Mesh : public Component
{
private:



public:
     QString FilePath ="";
    Mesh(const char* filePath,
         const char* vertexShaderPath = "shaders/phong.vert.spv",
         const char* fragmentShaderPath = "shaders/phong.frag.spv");
    void Update() override;

    void OnAttach() override;
    void UpdateTransform() override;


    Renderer::Drawable *GetRenderer();

    Renderer::Drawable* drawable;
};
