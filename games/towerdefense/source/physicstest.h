#ifndef PHYSICSTEST_H
#define PHYSICSTEST_H

#include "core/x-platform/scene.h"

class SphereCollider;

class PhysicsTest : public Scene
{
public:
    PhysicsTest();
    void Init();
    void Clean();

    GameObject* first;
    GameObject* second;
private:
    void Update(float deltaTime);

};

#endif // PHYSICSTEST_H
