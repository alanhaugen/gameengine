#pragma once

#include "component.h"

class SphereCollider : public Component
{
private:
    float r;
    int collisionResponse;

    enum
    {
        NONE,
        BOUNCE
    };

    Physics::Collider* collider;
    //Renderer::Drawable* hønsenetting;

public:
    SphereCollider(float innR = 1.0f, int collisionResponse = NONE);
    void Update();
};
