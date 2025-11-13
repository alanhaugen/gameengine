#include "spherecollider.h"

SphereCollider::SphereCollider(float innR, int response)
{
    radius = innR;
    collisionResponse = response;

    collider = physics->CreateCollider(DYNAMIC);
}

void SphereCollider::Update()
{
    //collider->SetPosition(id);
}
