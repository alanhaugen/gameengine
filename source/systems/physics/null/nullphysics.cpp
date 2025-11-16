#include "nullphysics.h"

bool NullPhysics::Init()
{
    return true;
}

void NullPhysics::Update()
{
}

bool NullPhysics::isColliding(GameObject *firstObject, GameObject *secondObject)
{
    return false;
}

Physics::Collider* NullPhysics::CreateCollider(GameObject* gameObject, float radius, int response)
{
    Collider collider;
    collider.gameObject = gameObject;

    colliders.push_back(Collider());

    return &colliders.back();
}
