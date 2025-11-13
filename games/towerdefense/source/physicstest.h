#ifndef PHYSICSTEST_H
#define PHYSICSTEST_H

#include "core/x-platform/scene.h"

class physicstest : public Scene
{
public:
    physicstest();
    void Init();
    void Clean();
private:
    void Update();

};

#endif // PHYSICSTEST_H
