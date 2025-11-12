#ifndef EMPTY_H
#define EMPTY_H

#include "core/x-platform/scene.h"

class Empty : public Scene
{
public:
    Empty();
    void Init();
    void Update();
    void Clean();
};

#endif // EMPTY_H
