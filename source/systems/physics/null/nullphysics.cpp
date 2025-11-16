#include "nullphysics.h"

bool NullPhysics::Init()
{
    return true;
}

void NullPhysics::Update()
{
}

Physics::Collider* NullPhysics::CreateCollider(GameObject* gameObject, int response)
{
    Collider* collider = new Collider();
    collider->gameObject = gameObject;

    colliders.push_back(Collider());

    return collider;
}
