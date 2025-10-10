#pragma once

#include "../physics.h"
#include <vector>

class NullPhysics : public Physics
{
private:
    std::vector<Collider> colliders;

public:
    void Init();
    void Update();
    Collider CreateCollider(int response);
};
