#pragma once

#include "component.h"

class SphereCollider : public Component
{
public:
    void Init();

private:
    Physics::Collider* collider;

public:
    SphereCollider(GameObject* gameObject, float innR = 1.0f, int collisionResponse = Physics::DYNAMIC);
    void Update();
};
