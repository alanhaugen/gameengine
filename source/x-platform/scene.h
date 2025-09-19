#pragma once

#include <vector>
#include "../components/component.h"

class Scene
{
private:

public:
    virtual void Init() = 0;
    virtual void Update(float time) = 0;

    std::vector<Component*> components;
};
