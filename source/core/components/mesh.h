#pragma once

#include "visualobject.h"

class Mesh : public VisualObject
{
public:
     QString FilePath ="";
    Mesh(const char* filePath,
         const char* vertexShaderPath = "shaders/phong.vert.spv",
         const char* fragmentShaderPath = "shaders/phong.frag.spv");
    void Update() override;
    void OnAttach() override;
    void UpdateTransform(Transform transform) override;
};
