#include "nullphysics.h"

bool NullPhysics::Init()
{
    return true;
}

void NullPhysics::Update()
{
}

Physics::Collider NullPhysics::CreateCollider(int response)
{
    colliders.push_back(Collider());
    return colliders.back();
}
