#include "trianglecollider.h"

TriangleCollider::TriangleCollider(float innR, int response)
{
    name = "Triangle Collider";
    r = innR;

    //collider = physics->CreateCollider(response);
}

void TriangleCollider::Update()
{
    //collider->SetPosition(id);
}
