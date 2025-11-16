#pragma once

#include "../physics.h"
#include <vector>

class NullPhysics : public Physics
{
private:
    std::vector<Collider> colliders;

public:
    bool Init();
    void Update();

    Collider* CreateCollider(GameObject* gameObject, float radius, int response);
};
