#pragma once

#include "../system.h"

class FileSystem : public System
{
public:
    virtual bool Init() = 0;
    virtual void Update() = 0;
};
