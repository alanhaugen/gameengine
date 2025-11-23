#include "boxcollider.h"

BoxCollider::BoxCollider(GameObject* inGameObject, int type)
{
    collider = physics->CreateCollider(inGameObject, type);
}

void BoxCollider::Update()
{
}
