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
    bool Collision(const char* type = 0);
    Collider CreateCollider(int response);
};
