#include "spherecollider.h"

SphereCollider::SphereCollider(float innR, int response)
{
    r = innR;
    collisionResponse = response;

    //collider = physics->CreateSphereCollider();
}

void SphereCollider::Update()
{
    //collider->SetPosition(id);
}
