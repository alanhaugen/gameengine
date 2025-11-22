#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H

#include "core/x-platform/scene.h"
#include "core/components/timer.h"
#include "core/components/sphere.h"
#include "core/components/terrain.h"

class BSplineCurve
{
public:
    // Determines how many control points influence each segment and
    // how smooth the curve is
    // f. ex. d = 3 would mean a cubic B-spline.
    int degree = 3;
    std::vector<float> t; // knot vector, the length of t should be n + d + 2
    std::vector<glm::vec3> controlPoints;

private:
    float findKnotInterval(float x)
    {
        int my = controlPoints.size() - 1; // indekstilsistekontrollpunkt

        while (x < t[my])
        {
            my--;
        }

        return my;
    }

public:
    glm::vec3 EvaluateBSplineSimple(float x)
    {
        int my = findKnotInterval(x);
        std::vector<glm::vec3> a;

        a.resize(degree+1);

        for (int i = 0; i <= degree; i++)
        {
            a[degree-i] = controlPoints[my-i];
        }

        for (int k = degree; k > 0; k--)
        {
            int j = my - k;

            for (int i = 0; i < k; i++)
            {
                j++;

                float w = (x - t[j])/(t[j+k] - t[j]);

                a[i] = a[i] * (1-w) + a[i+1] * w;
            }
        }

        return a[0];
    }
};

// Move this into physics...
class Ball : public Component
{
public:
    Sphere* ballMesh;
    Terrain* terrainMesh;
    glm::vec3 velocity;
    glm::vec3 gravity = glm::vec3(0, -0.98, 0);

    float acceleration = 1.0f;
    float mass = 1.0f;

    Ball(Terrain* terrain = nullptr, const char* texture = "")
    {
        ballMesh = new Sphere(texture);
        terrainMesh = terrain;
    }

    void Update()
    {
        glm::vec3 pos;

        if (gameObject)
        {
            pos = gameObject->GetPosition();
            ballMesh->drawable->ubo.model = gameObject->matrix;
        }
        else
        {
            pos = ballMesh->GetPosition();
        }

        velocity += terrainMesh->GetNormal(pos) / 500.0f;
        velocity -= velocity * terrainMesh->GetFriction(pos);// * deltaTime;
        velocity.y = 0.0f;

        pos += velocity;
        pos.y = terrainMesh->GetHeightAt(pos) + 1.0f;

        if (glm::length(velocity) > 0.0001f)
        {
            glm::vec3 rollVector = glm::normalize(glm::cross(glm::normalize(velocity), terrainMesh->GetNormal(pos)));

            if (glm::length(rollVector) > 0.0001f)
            {
                if (gameObject)
                {
                    gameObject->Rotate((glm::length(velocity)), rollVector);
                }
            }
        }

        if (gameObject)
        {
            gameObject->SetPosition(pos);
        }
        else
        {
            ballMesh->SetPosition(pos);
        }
    }
};

class InstancedBall : public Ball
{
public:
    InstancedBall(Terrain* terrain = nullptr)
    {
        ballMesh = new Sphere(glm::vec3(1.0f),
                              glm::vec3(0.0f / 256.0f, 124.0f / 256.0f, 181.0f / 256.0f),
                              "shaders/instanced.vert.spv",
                              "shaders/instanced.frag.spv");
        terrainMesh = terrain;
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
