#pragma once

#include <glm/glm.hpp>
#include "../system.h"

class GameObject;

class Physics : public System
{
public:
    enum CollisionResponse
    {
        STATIC,
        DYNAMIC
    };

    class Collider
    {
    public:
        float radius;
        float mass;
        float velocity;
        GameObject* gameObject;

    private:
    };

    virtual bool Init() = 0;
    virtual void Update() = 0;
    virtual Collider* CreateCollider(GameObject* gameObject, float radius, int response) = 0;
};
