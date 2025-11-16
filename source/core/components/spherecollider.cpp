#include "spherecollider.h"

SphereCollider::SphereCollider(float innR, int response)
{
    radius = innR;
    collisionResponse = response;

    collider = physics->CreateCollider(gameObject, DYNAMIC);
}

void SphereCollider::Update()
{
}
