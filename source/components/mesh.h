#pragma once

#include "component.h"
#include "../modules/renderer/renderer.h"
#include "glm/glm.hpp"

class Mesh : public Component
{
private:
    Renderer::Drawable* drawable;

public:
    Mesh(const char* filePath);
    void Update();

    glm::f32mat4x4 matrix;
};
