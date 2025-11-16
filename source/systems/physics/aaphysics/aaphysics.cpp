#include "aaphysics.h"
#include <core/components/gameobject.h>
#include <core/x-platform/locator.h>

AAPhysics::AAPhysics() {}

bool AAPhysics::Init() { return true; }

void AAPhysics::Update()
{
    ApplyGravity();
    CollisionDetection();
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
                // collision
                Log("Collision");
            }
            else
            {
                Log("No Collision");
            }
        }
    }
}

void AAPhysics::CollisionResponse(Collider* colliderA, Collider* colliderB)
{
    //calculateImpulses(bodyA.mass, bodyB.mass, bodyA.speed, bodyB.speed);
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

    colliders.push_back(collider);

    return &colliders.back();
}
