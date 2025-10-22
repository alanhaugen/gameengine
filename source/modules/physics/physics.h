#pragma once

#include "../system.h"

class Physics : public System
{
public:
    enum CollisionResponse
    {
        NONE,
        BOUNCE
    };

    class Collider
    {
    public:
    private:
    };

    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual bool Collision(const char* type = 0) = 0;
    virtual Collider CreateCollider(int response) = 0;
};
