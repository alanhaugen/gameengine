#pragma once

#include "../physics.h"

class NullPhysics : public Physics
{
public:
    void Init();
    void Update();
};
