#include "spherecollider.h"

SphereCollider::SphereCollider(GameObject* gameObject, float innR, int response)
{
    name = "Sphere Collider";
    collider = physics->CreateCollider(gameObject, innR, Physics::DYNAMIC);
}

void SphereCollider::Update(float deltaTime)
{
}

bool SphereCollider::IsCollided()
{
    return collider->isColliding;
}
