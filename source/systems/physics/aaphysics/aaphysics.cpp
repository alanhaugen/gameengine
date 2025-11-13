#include "aaphysics.h"

AAPhysics::AAPhysics() {}

bool AAPhysics::Init() { return true; }

void AAPhysics::Update()
{
    ApplyGravity();
    CollisionDetection();
}

void AAPhysics::ApplyGravity(float deltaTime) {}

void AAPhysics::CollisionDetection()
{
    // Implement broad and narrow phase
    for (int i = 0; i < sceneColliders.size(); i++)
    {
        for (int j = 0; j < sceneColliders.size(); j++)
        {
            glm::vec3 diff = sceneColliders[j]->center - sceneColliders[i]->center;
            float doubleRadiance = sceneColliders[i]->radius + sceneColliders[j]->radius;
            float distSquared = glm::dot(diff, diff);

            if (distSquared < doubleRadiance)
            {
                if (sceneColliders[i] == sceneColliders[j])
                {
                    return;
                }
                else
                {
                    CollisionResponse(sceneColliders[i], sceneColliders[j]);
                    //Log("Collision");
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

Physics::Collider* AAPhysics::CreateCollider(int response)
{
    Collider* collider = new Collider();

    sceneColliders.push_back(collider);

    return collider;
    //return Physics::Collider();
}
