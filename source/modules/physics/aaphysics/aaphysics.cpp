#include "aaphysics.h"

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
}

void AAPhysics::ApplyGravity(float deltaTime)
{

}

void AAPhysics::CollisionDetection()
{
    for (int i = 0; i < sceneColliders.size(); i++)
    {
        for (int j = 0; j < sceneColliders.size(); j++)
        {
            //if sceneColliers[i] != sceneCollier
        }
    }
}

Physics::Collider* AAPhysics::CreateCollider(int response)
{
    Collider* collider = new Collider();

    sceneColliders.push_back(collider);

    return collider;
    //return Physics::Collider();
}
