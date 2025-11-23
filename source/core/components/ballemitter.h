#ifndef BALLEMITTER_H
#define BALLEMITTER_H

#include "core/components/component.h"
#include "core/components/terrain.h"
#include "core/components/sphere.h"
#include "core/components/rigidbody.h"

class InstancedBall : public Component
{
public:
    Terrain* terrainMesh;
    Sphere* ballMesh;
    RigidBody* rigidBody;

    InstancedBall(Terrain* terrain = nullptr)
    {
        ballMesh = new Sphere(glm::vec3(1.0f),
                              glm::vec3(0.0f / 256.0f, 124.0f / 256.0f, 181.0f / 256.0f),
                              "shaders/instanced.vert.spv",
                              "shaders/instanced.frag.spv");
        terrainMesh = terrain;
        rigidBody = new RigidBody(terrain);
        ballMesh->Hide();
    }

    void Update()
    {
        rigidBody->Update(ballMesh);
        ballMesh->Update();
    }
};

class BallEmitter : public Component
{
public:
    std::vector<InstancedBall*> balls;
    std::vector<bool> active;

    BallEmitter(Terrain* terrain);
    void Update();
    void Reset();
};

#endif // BALLEMITTER_H
