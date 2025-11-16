#pragma once

#include "core/x-platform/locator.h"

class GameObject;

class Component : public Locator
{
public:
    std::string name;
    GameObject* gameObject;
    virtual void Update() = 0;
};
