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

    enum CollisionShape
    {
        SPHERE,
        BOX
    };

    struct Collider
    {
        float radius;
        int response;
        int shape;
        glm::vec3 oldPosition;
        //float mass;
        //float velocity;
        bool isColliding;
        GameObject* gameObject;
        GameObject* collidesWithObject;
    };

    class Ray
    {
    public:
        Ray(const glm::vec3 &orig, const glm::vec3 &dir) : origin(orig), dir(dir)
        {
            invdir.x = 1.0f / dir.x;
            invdir.y = 1.0f / dir.y;
            invdir.z = 1.0f / dir.z;
            sign[0] = (invdir.x < 0);
            sign[1] = (invdir.y < 0);
            sign[2] = (invdir.z < 0);
        }
        glm::vec3 origin, dir;       // ray orig and dir
        glm::vec3 invdir;
        int sign[3];
    };

    virtual bool Init() = 0;
    virtual void Update() = 0;
    virtual bool isColliding(Ray ray, GameObject* gameObject) = 0;
    virtual bool isColliding(GameObject* firstObject, GameObject* secondObject = nullptr) = 0;
    virtual Collider* CreateCollider(GameObject* gameObject, float radius, int response) = 0;
    virtual Collider* CreateCollider(GameObject* gameObject, int response) = 0;
};
