#ifndef EMPTY_H
#define EMPTY_H

#include "core/x-platform/scene.h"
#include "core/components/mesh.h"
#include "core/components/text.h"
#include "core/components/cube.h"

class Empty : public Scene
{
public:
    Empty();
    void Init();
    void Update();
    void Clean();
};

#endif // EMPTY_H
