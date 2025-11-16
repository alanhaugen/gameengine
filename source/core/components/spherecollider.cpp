#include "spherecollider.h"

SphereCollider::SphereCollider(GameObject* gameObject, float innR, int response)
{
    collider = physics->CreateCollider(gameObject, innR, Physics::DYNAMIC);
}

void SphereCollider::Update()
{
}
