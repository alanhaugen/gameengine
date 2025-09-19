#pragma once

#include <vector>
#include "../components/component.h"
#include "../modules/renderer/renderer.h"

class Scene
{
public:
    virtual void Init() = 0;
    virtual void Update(float time) = 0;

    std::vector<Component*> components;

    Renderer* renderer;
};
