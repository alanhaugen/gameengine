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
            glm::vec3 diff = colliders[j]->center - colliders[i]->center;
            float doubleRadiance = colliders[i]->radius + colliders[j]->radius;
            float distSquared = glm::dot(diff, diff);

            if (distSquared < doubleRadiance)
            {
                if (colliders[i] == colliders[j])
                {
                    return;
                }
                else
                {
                    CollisionResponse(colliders[i], colliders[j]);
                    Log("Collision");
                }
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

Physics::Collider* AAPhysics::CreateCollider(GameObject* gameObject, int response)
{
    Collider* collider = new Collider();
    collider->gameObject = gameObject;

    colliders.push_back(collider);

    return collider;
    //return Physics::Collider();
}
