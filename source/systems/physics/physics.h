#pragma once

#include <glm/glm.hpp>
#include "../system.h"

class GameObject;

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
        float radius;
        float mass;
        float velocity;
        glm::vec3 center;
        GameObject* gameObject;

    private:
    };

    virtual bool Init() = 0;
    virtual void Update() = 0;
    virtual Collider* CreateCollider(GameObject* gameObject, int response) = 0;
};
