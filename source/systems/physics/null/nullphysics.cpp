#include "nullphysics.h"

bool NullPhysics::Init()
{
    return true;
}

void NullPhysics::Update()
{
}

bool NullPhysics::isColliding(Ray ray, GameObject *gameObject)
{
    return false;
}

bool NullPhysics::isColliding(GameObject *firstObject, GameObject *secondObject)
{
    return false;
}

Physics::Collider *NullPhysics::CreateCollider(GameObject *gameObject, int response)
{
    return nullptr;
}

Physics::Collider* NullPhysics::CreateCollider(GameObject* gameObject, float radius, int response)
{
    return nullptr;
}
