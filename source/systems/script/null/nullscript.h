#pragma once

#include "../script.h"

class NullScript : public Script
{
public:
    bool Init();
    void Update();
};
