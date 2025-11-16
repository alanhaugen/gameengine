#pragma once

#include "core/x-platform/locator.h"

class GameObject;

class Component : public Locator
{
public:
    std::string name = "Component";
    GameObject* gameObject = nullptr;
    virtual void Update() = 0;
};
