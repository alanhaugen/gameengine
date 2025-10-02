#pragma once

#include "../filesystem.h"

class NullFileSystem : public FileSystem
{
public:
    bool Init();
    void Update();
};
