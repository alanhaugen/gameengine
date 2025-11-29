#ifndef BALLEMITTER_H
#define BALLEMITTER_H

#include "core/components/component.h"
#include "core/components/terrain.h"
#include "core/components/sphere.h"
#include "core/components/rigidbody.h"
#include "core/components/trackingspline.h"

class InstancedBall : public Component
{
public:
    Terrain* terrainMesh;
    Sphere* ballMesh;
    RigidBody* rigidBody;
    TrackingSpline* tracking;

    InstancedBall(Terrain* terrain = nullptr)
    {
        ballMesh = new Sphere(glm::vec3(1.0f),
                              glm::vec3(0.0f / 256.0f, 124.0f / 256.0f, 181.0f / 256.0f),
                              "shaders/color.vert.spv",
                              "shaders/color.frag.spv", false);
        tracking = new TrackingSpline();
        tracking->followObject = ballMesh;
        tracking->recreateSplineTime = 1500.0f;
        terrainMesh = terrain;
        rigidBody = new RigidBody(terrain);
        ballMesh->Hide();
    }

    void Update()
    {
        if (renderer->isVisible(ballMesh->drawable))
        {
            tracking->Update();
        }

        rigidBody->Update(ballMesh);
        ballMesh->Update();
    }
};

class BallEmitter : public Component
{
public:
    std::vector<InstancedBall*> balls;
    std::vector<bool> active;
    std::vector<glm::vec3> ballVelocities;

    BallEmitter(Terrain* terrain);
    void Update();
    void Reset();
};

#endif // BALLEMITTER_H
