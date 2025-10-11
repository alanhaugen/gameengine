#pragma once

#include "component.h"

class Terrain : public Component
{
private:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

public:
    Terrain(const char* filePath,
         const char* vertexShaderPath = "shaders/color.vert.spv",
         const char* fragmentShaderPath = "shaders/color.frag.spv");
    void Update();

    Renderer::Drawable* drawable;
    float GetHeightAt(const glm::vec3 positionXZ) const;
};
