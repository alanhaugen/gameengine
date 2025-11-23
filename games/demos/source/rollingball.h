#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H

#include "core/x-platform/scene.h"

class BallEmitter;
class Terrain;

class RollingBall : public Scene
{
public:
    void Init();
    void Update(float deltaTime);

    GameObject* ball;

    GameObject* particleSystem;
    BallEmitter* ballSystem;

    GameObject* cube;

    GameObject* terrain;
    Terrain* terrainMesh;
    Terrain* terrainMeshPoints;
};

#endif // ROLLINGBALL_H
