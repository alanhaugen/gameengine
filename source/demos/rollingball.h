#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H

#include "../x-platform/scene.h"

class Mesh;

class RollingBall : public Scene
{
public:
    RollingBall();
    void Init();
    void Update();

    float force = 0.0f;

    Mesh* ballMesh;
};

#endif // ROLLINGBALL_H
