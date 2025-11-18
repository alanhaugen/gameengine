#include "rollingball.h"
#include "core/platforms/application.h"
#include "core/components/mesh.h"
#include "core/components/terrain.h"
#include <glm/gtc/matrix_transform.hpp>

RollingBall::RollingBall()
{
}

void RollingBall::Init()
{
    ball = new GameObject("Ball");
    ball->AddComponent(new Mesh("Assets/Models/ball.obj"));

    //terrainMeshPoints = new Terrain("Assets/PointClouds/snoehetta/output_smallest.txt", true);//("Assets/blurred.png", "Assets/Textures/forrest_ground_01_diff_1k.jpg");//("Assets/terrain.png");
    terrainMesh = new Terrain("tools/pointconverter/output.png", "Assets/Textures/snow.jpg");//("Assets/blurred.png", "Assets/Textures/forrest_ground_01_diff_1k.jpg");//("Assets/terrain.png");

    camera.position = glm::vec3(4.0f, 10.0f, 40.0f);

    sampleTimer.Start();
}

void RollingBall::Update(float deltaTime)
{
    glm::vec3 pos = ball->GetPosition();

    if (input.Held(input.Key.R))
    {
        sampleTimer.Reset();
        points.clear();

        curve = BSplineCurve();

        pos = camera.position;
        velocity = glm::vec3(camera.forward / 90.0f);
    }

    if (glm::length(velocity) > 0.0001f && sampleTimer.TimeSinceStarted() > 500.0f)
    {
        sampleTimer.Reset();
        curve.controlPoints.push_back(pos);
        points.push_back(pos);

        if (splineDrawable)
        {
            //linesDrawable->isVisible = false;
            splineDrawable->isVisible = false;
        }

        std::vector<Vertex> vertices;

        // Recompute knot vector
        int n = curve.controlPoints.size() - 1;
        int d = curve.degree;
        curve.t.resize(n + d + 2);
        for (int i = 0; i < n + d + 2; ++i)
            curve.t[i] = float(i);

        // Sample curve
        float uStart = curve.t[d];
        float uEnd   = curve.t[curve.t.size() - d - 1];

        for (float f = 0.0f; f <= 1.0f; f += 0.01f)
        {
            float u = glm::mix(uStart, uEnd, f);
            vertices.push_back(Vertex(curve.EvaluateBSplineSimple(u), glm::vec3(1,1,1)));
        }

        splineDrawable = &renderer->CreateDrawable(vertices, std::vector<unsigned>(), "shaders/color.vert.spv", "shaders/color.frag.spv", Renderer::LINES_STRIP);
        //linesDrawable = &renderer->CreateDrawable(points, std::vector<unsigned>(), "shaders/color.vert.spv", "shaders/color.frag.spv", Renderer::LINES_STRIP);
    }

    /*if (input.Held(input.Key.SPACE))
    {
        Application::NextScene();
    }*/

    velocity += terrainMesh->GetNormal(pos) / 500.0f;
    velocity -= velocity * frictionCoeff * deltaTime;
    velocity.y = 0.0f;

    pos += velocity;
    pos.y = terrainMesh->GetHeightAt(pos) + 1.0f;

    if (glm::length(velocity) > 0.0001f)
    {
        glm::vec3 rollVector = glm::normalize(glm::cross(glm::normalize(velocity), terrainMesh->GetNormal(pos)));

        if (glm::length(rollVector) > 0.0001f)
        {
            ball->Rotate((glm::length(velocity)), rollVector);
        }
    }

    ball->SetPosition(pos);
}
