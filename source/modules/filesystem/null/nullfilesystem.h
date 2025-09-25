#pragma once

#include "../filesystem.h"

class NullFileSystem : public FileSystem
{
public:
    void Init();
    void Update();
};
