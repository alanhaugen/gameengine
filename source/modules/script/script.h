#pragma once

#include "../system.h"

class Script : public System
{
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
};
