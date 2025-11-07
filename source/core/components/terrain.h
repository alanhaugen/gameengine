#pragma once

#include "visualobject.h"

class Terrain : public VisualObject
{
private:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    void Init();

public:
    Terrain();
    Terrain(const char* filePath,
            const char* texturePath = "",
            const char* vertexShaderPath = "shaders/color.vert.spv",
            const char* fragmentShaderPath = "shaders/color.frag.spv");
    void Update();

    float GetHeightAt(float x, float z) const;
    float GetHeightAt(const glm::vec3 positionXZ) const;
    glm::vec3 GetNormal(const glm::vec3 position) const;
};
