#include "nullphysics.h"

bool NullPhysics::Init()
{
    return true;
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
