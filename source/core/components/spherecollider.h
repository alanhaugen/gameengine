#pragma once

#include "component.h"

class SphereCollider : public Component
{
public:
    SphereCollider(GameObject* gameObject, float innR = 1.0f, int collisionResponse = Physics::DYNAMIC);
    void Init();
    void Update();

    Physics::Collider* collider;
};
