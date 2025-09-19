#pragma once

#include "component.h"
#include "../modules/renderer/renderer.h"

class Mesh : public Component
{
private:

public:
    Mesh(const char* filePath, Renderer* renderer);
    void Update();

    Renderer::Drawable* drawable;
};
