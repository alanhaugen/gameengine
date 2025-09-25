#pragma once

#include <vector>
#include "editor.h"
#include "../components/component.h"
#include "../modules/renderer/renderer.h"
#include "../components/GameObject.h"

class Scene
{
public:
    virtual void Init() = 0;
    virtual void Update() = 0;

    std::vector<Component*> components;

     std::vector<GameObject*> GameObjects;

    Renderer* renderer;
    Editor* editor;
};
