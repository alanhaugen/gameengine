#pragma once

#include <vector>
#include "core/components/gameobject.h"
#include "core/components/camera.h"
#include "locator.h"

class Scene : public Locator
{
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Clean() = 0;


    Camera camera;
    unsigned id;

    std::vector<GameObject*> gameObjects;
};
