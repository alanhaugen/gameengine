#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H

#include "core/components/rigidbody.h"
#include "core/x-platform/scene.h"
#include "core/components/timer.h"
#include "core/components/sphere.h"
#include "core/components/terrain.h"
#include "core/x-platform/bsplinecurve.h"

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

class BallParticleSystem : public Component
{
public:
    std::vector<InstancedBall*> balls;
    std::vector<bool> active;

    BallParticleSystem(Terrain* terrain = nullptr)
    {
        for (int i = 0; i < 1500; i++)
        {
            balls.push_back(new InstancedBall(terrain));
        }

        for (int i = 0; i < balls.size(); i++)
        {
            active.push_back(false);
        }
    }

    void Reset()
    {
        for (int i = 0; i < active.size(); i++)
        {
            balls[i]->ballMesh->Hide();
            active[i] = false;
        }
    }

    void Update()
    {
        for (int i = 0; i < balls.size(); i++)
        {
            balls[i]->Update();
        }

        for (int i = 0; i < active.size(); i++)
        {
            if (active[i] == false)
            {
                active[i] = true;
                balls[i]->ballMesh->Show();
                float randomNumber1 = rand() % 5;
                float randomNumber2 = rand() % 5;
                randomNumber1 -= randomNumber1 / 2;
                randomNumber2 -= randomNumber2 / 2;
                balls[i]->ballMesh->SetPosition(gameObject->GetPosition() + glm::vec3(randomNumber1,0,randomNumber2));
                break;
            }
        }
    }
};

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
    BallParticleSystem* ballSystem;

    GameObject* cube;

    Timer sampleTimer;

    int index = 0;

    GameObject* terrain;
    Terrain* terrainMesh;
    Terrain* terrainMeshPoints;
};

#endif // ROLLINGBALL_H
