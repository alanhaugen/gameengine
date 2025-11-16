#include "nullphysics.h"

bool NullPhysics::Init()
{
    return true;
}

void NullPhysics::Update()
{
}

Physics::Collider* NullPhysics::CreateCollider(GameObject* gameObject, float radius, int response)
{
    Collider collider;
    collider.gameObject = gameObject;

    colliders.push_back(Collider());

    return &colliders.back();
}
