#include "aaphysics.h"

AAPhysics::AAPhysics()
{

}

bool AAPhysics::Init()
{
    return false;
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

}

Physics::Collider AAPhysics::CreateCollider(int response)
{
    return Physics::Collider();
}
