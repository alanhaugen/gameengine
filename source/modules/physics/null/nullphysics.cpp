#include "nullphysics.h"

void NullPhysics::Init()
{

}

void NullPhysics::Update()
{
}

bool NullPhysics::Collision(const char *type)
{
    return false;
}

Physics::Collider NullPhysics::CreateCollider(int response)
{
    colliders.push_back(Collider());
    return colliders.back();
}
