#include "nullphysics.h"

bool NullPhysics::Init()
{
    return true;
}

void NullPhysics::Update()
{
}


Physics::Collider* NullPhysics::CreateCollider(int response)
{
    Collider* collider = new Collider();

    colliders.push_back(Collider());

    return collider;
}
