#pragma once

#include "component.h"

class VisualObject : public Component
{
public:
    Renderer::Drawable* drawable;
};
