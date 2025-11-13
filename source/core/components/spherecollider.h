#pragma once

#include "component.h"

class SphereCollider : public Component
{
public:
    float velocity;
    void Init();

private:
    glm::vec3 center;
    float mass;
    float radius;
    int collisionResponse;

    enum
    {
        NONE,
        STATIC, // Wont receive force/impulse, but will affect other solid colliders
        DYNAMIC // Will receive force/impulse and affect other solid colliders
    };

    Physics::Collider* collider;

public:
    SphereCollider(float innR = 1.0f, int collisionResponse = NONE);
    void Update();
};
