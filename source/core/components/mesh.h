#pragma once

#include "visualobject.h"

class Mesh : public VisualObject
{
public:
    std::string FilePath = "";
    Mesh(const char* filePath,
         const char* vertexShaderPath = "shaders/phong.vert.spv",
         const char* fragmentShaderPath = "shaders/phong.frag.spv");

    void loadMesh(const char* filePath,
                   const char* vertexShaderPath = "shaders/phong.vert.spv",
                   const char* fragmentShaderPath = "shaders/phong.frag.spv");
    void loadMeshGLTF(const char* filePath,
                   const char* vertexShaderPath = "shaders/phong.vert.spv",
                   const char* fragmentShaderPath = "shaders/phong.frag.spv");
    void Update() override;

   std::string texture = "";

   std::string GetFileExtension(const char* string);
};
