#pragma once

#include "component.h"
#include "systems/physics/physics.h"

class TriangleCollider : public Component
{
private:
    float r;
    Physics::Collider collider;

public:
    TriangleCollider(float innR = 1.0f,
                     int collisionResponse = Physics::CollisionResponse::NONE);
    void Update();
};
