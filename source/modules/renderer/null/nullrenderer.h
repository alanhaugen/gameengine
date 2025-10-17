#pragma once

#include "../renderer.h"
#include <vector>

class NullRenderer : public Renderer
{
private:
    std::vector<Drawable> drawables;

public:
    void Init();
    void Update();

    Drawable& CreateDrawable(std::vector<Vertex> vertices,
                             std::vector<uint32_t> indices,
                             const char* vertexShader = "shaders/vert.spv",
                             const char* fragmentShader = "shaders/frag.spv",
                             const int topology = TRIANGLES,
                             const char* texture = "");

    void SetViewMatrix(glm::mat4 view);
    void SetCameraPosition(glm::vec3 pos);
    void SetLightPos(glm::vec3 pos);
};
