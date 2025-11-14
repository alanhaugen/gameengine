#pragma once

#include "visualobject.h"

class Mesh : public VisualObject
{
public:
    std::string FilePath = "";
    Mesh(const char* filePath,
         const char* vertexShaderPath = "shaders/phong.vert.spv",
         const char* fragmentShaderPath = "shaders/phong.frag.spv");

     //loads mesh
    void loadMesh(const char* filePath,
                   const char* vertexShaderPath = "shaders/phong.vert.spv",
                   const char* fragmentShaderPath = "shaders/phong.frag.spv");
    void Update() override;
    void OnAttach() override;
    void UpdateTransform(Transform transform) override;
};
