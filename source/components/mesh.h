#pragma once

#include "component.h"
#include "../modules/renderer/renderer.h"

class Mesh : public Component
{
private:
    Drawable* drawable;

public:
    Mesh(const char* filePath);
};
