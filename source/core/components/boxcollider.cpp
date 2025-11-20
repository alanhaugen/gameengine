#include "boxcollider.h"

BoxCollider::BoxCollider()
{
    collider = physics->CreateCollider(gameObject, Physics::STATIC);
}

void BoxCollider::Update()
{
}
