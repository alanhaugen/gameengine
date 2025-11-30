#include "boxcollider.h"

BoxCollider::BoxCollider(GameObject* inGameObject, int type)
{
    name = "Box Collider";

    collider = physics->CreateCollider(inGameObject, type);
}

void BoxCollider::Update(float deltaTime)
{
}

bool BoxCollider::IsColliding()
{
    return collider->isColliding;
}
