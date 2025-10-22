#include "aaphysics.h"

AAPhysics::AAPhysics()
{

}

void AAPhysics::Init()
{

}

void AAPhysics::Update()
{
    ApplyGravity();
    CollisionDetection();
}

bool AAPhysics::Collision(const char *type)
{
    return false;
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
