#pragma once

#include <vector>
#include "../components/gameobject.h"
#include "../components/camera.h"
#include "locator.h"

class Scene : public Locator
{
public:
    virtual void Init() = 0;
    virtual void Update() = 0;

    Camera camera;

    std::vector<GameObject*> gameObjects;
};
