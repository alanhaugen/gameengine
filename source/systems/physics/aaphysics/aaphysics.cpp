#include "aaphysics.h"
#include <core/components/gameobject.h>
#include <core/x-platform/locator.h>

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

AAPhysics::AAPhysics()
{
}

bool AAPhysics::Init()
{
    return true;
}

void AAPhysics::Update()
{
    ApplyGravity();
    CollisionDetection();

    for (int i = 0; i < colliders.size(); i++)
    {
        colliders[i].oldPosition = colliders[i].gameObject->GetPosition();
    }
}

bool AAPhysics::isColliding(Ray ray, GameObject *gameObject)
{
    if (gameObject->isVisible == false)
    {
        return false;
    }

    // lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
    // ray.orig is origin of ray
    float lbx = gameObject->GetPosition().x - gameObject->dimensions.x;
    float rtx = gameObject->GetPosition().x + gameObject->dimensions.x;
    float lby = gameObject->GetPosition().y - gameObject->dimensions.y;
    float rty = gameObject->GetPosition().y + gameObject->dimensions.y;
    float lbz = gameObject->GetPosition().z + gameObject->dimensions.z;
    float rtz = gameObject->GetPosition().z - gameObject->dimensions.z;

    float t1 = (lbx - ray.origin.x) * ray.invdir.x;
    float t2 = (rtx - ray.origin.x) * ray.invdir.x;
    float t3 = (lby - ray.origin.y) * ray.invdir.y;
    float t4 = (rty - ray.origin.y) * ray.invdir.y;
    float t5 = (lbz - ray.origin.z) * ray.invdir.z;
    float t6 = (rtz - ray.origin.z) * ray.invdir.z;

    float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
    float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

    // if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
    if (tmax < 0)
    {
        //t = tmax;
        return false;
    }

    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax)
    {
        //t = tmax;
        return false;
    }

    //t = tmin;
    return true;
}

bool AAPhysics::isColliding(GameObject *firstObject, GameObject *secondObject)
{
    for (int i = 0; i < colliders.size(); i++)
    {
        if (colliders[i].gameObject == firstObject && colliders[i].isColliding)
        {
            if (secondObject == nullptr)
            {
                return true;
            }
            else if (secondObject == colliders[i].collidesWithObject)
            {
                return true;
            }
        }
    }

    return false;
}

void AAPhysics::ApplyGravity(float deltaTime)
{
}

void AAPhysics::CollisionDetection()
{
    // Implement broad and narrow phase
    for (int i = 0; i < colliders.size(); i++)
    {
        for (int j = 0; j < colliders.size(); j++)
        {
            // Do not detect against self
            if (colliders[i].gameObject == colliders[j].gameObject)
            {
                continue;
            }

            // Calculate sphere collision
            glm::vec3 diff = colliders[j].gameObject->GetPosition() - colliders[i].gameObject->GetPosition();
            float radiusSum = colliders[i].radius + colliders[j].radius;
            float distSquared = glm::dot(diff, diff);

            if (distSquared < radiusSum * radiusSum)
            {
                colliders[i].isColliding = true;
                colliders[i].collidesWithObject = colliders[j].gameObject;
                CollisionResponse(&colliders[i], &colliders[j]);
            }
            else
            {
                colliders[i].isColliding = false;
                colliders[i].collidesWithObject = nullptr;
            }
        }
    }
}

void AAPhysics::CollisionResponse(Collider* colliderA, Collider* colliderB)
{
    //calculateImpulses(bodyA.mass, bodyB.mass, bodyA.speed, bodyB.speed);
    if (colliderA->response == DYNAMIC)
    {
        colliderA->gameObject->SetPosition(colliderA->oldPosition);
    }
    if (colliderB->response == DYNAMIC)
    {
        colliderB->gameObject->SetPosition(colliderB->oldPosition);
    }
}

void AAPhysics::CalculateImpulses(float massA, float massB, float speedA, float speedB)
{
    //formel for inelastisk kollisjon: m1v1 + m2v2 = m1v1' + m2v2'
}

Physics::Collider* AAPhysics::CreateCollider(GameObject* gameObject, float radius, int response)
{
    Collider collider;
    collider.gameObject = gameObject;
    collider.radius = radius;
    collider.isColliding = false;
    collider.response = response;
    collider.oldPosition = gameObject->GetPosition();

    colliders.push_back(collider);

    return &colliders.back();
}
