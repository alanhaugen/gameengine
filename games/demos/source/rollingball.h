#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H

#include "core/x-platform/scene.h"
#include "core/components/timer.h"
#include "core/components/terrain.h"
#include "core/x-platform/bsplinecurve.h"

class BallEmitter;

class RollingBall : public Scene
{
public:
    void Init();
    void Update(float deltaTime);

    BSplineCurve curve;

    GameObject* ball;
    Renderer::Drawable* splineDrawable = nullptr;
    Renderer::Drawable* linesDrawable = nullptr;
    std::vector<Vertex> points;

    GameObject* particleSystem;
    BallEmitter* ballSystem;

    GameObject* cube;

    Timer sampleTimer;

    int index = 0;

    GameObject* terrain;
    Terrain* terrainMesh;
    Terrain* terrainMeshPoints;
};

#endif // ROLLINGBALL_H
