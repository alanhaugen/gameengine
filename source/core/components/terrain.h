#pragma once

#include "visualobject.h"

class Terrain : public VisualObject
{
private:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    int width,height;

    void Init();

public:
    Terrain();
    Terrain(const char* filePath,
            const bool isCloud);
    Terrain(const char* filePath,
            const char* texturePath = "",
            const char* vertexShaderPath = "shaders/phong.vert.spv",
            const char* fragmentShaderPath = "shaders/phong.frag.spv");
    void Update();

    float GetHeightAt(float x, float z) const;
    float GetHeightAt(const glm::vec3 positionXZ) const;
    glm::vec3 GetNormal(const glm::vec3 position) const;
    float GetFriction(const glm::vec3 position) const;
};
