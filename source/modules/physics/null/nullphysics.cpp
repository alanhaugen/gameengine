#include "nullphysics.h"

void NullPhysics::Init()
{

}

void NullPhysics::Update()
{
}

Physics::Collider NullPhysics::CreateCollider(int response)
{
    colliders.push_back(Collider());
    return colliders.back();
}
