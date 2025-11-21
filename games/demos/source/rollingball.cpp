#include "rollingball.h"
#include "core/components/boxcollider.h"
#include "core/components/cube.h"

void RollingBall::Init()
{
    cube = new GameObject("Cube");
    cube->AddComponent(new Cube);
    cube->AddComponent(new BoxCollider);
    cube->SetPosition(320, 300, 0);

    //terrainMeshPoints = new Terrain("Assets/PointClouds/snoehetta/output_smallest.txt", true);//("Assets/blurred.png", "Assets/Textures/forrest_ground_01_diff_1k.jpg");//("Assets/terrain.png");
    terrainMesh = new Terrain("tools/pointconverter/output.png", "Assets/Textures/snow.jpg");//("Assets/blurred.png", "Assets/Textures/forrest_ground_01_diff_1k.jpg");//("Assets/terrain.png");

    particleSystem = new GameObject("Ball Particle Emitter");
    ballSystem = new BallParticleSystem(terrainMesh);
    particleSystem->AddComponent(ballSystem);
    particleSystem->SetPosition(300,300,500);

    ball = new GameObject("Ball");
    ball->AddComponent(new Ball(terrainMesh, "Assets/Textures/orange.jpg"));

    camera.position = glm::vec3(300.f, 300.0f, 500.0f);

    sampleTimer.Start();
}

void RollingBall::Update(float deltaTime)
{
    particleSystem->Update();

    cube->SetPosition(cube->GetPosition().x,
                      terrainMesh->GetHeightAt(cube->GetPosition()),
                      cube->GetPosition().z);

    if (input.Held(input.Key.R))
    {
        sampleTimer.Reset();
        points.clear();

        curve = BSplineCurve();
        ballSystem->Reset();

        ball->SetPosition(camera.position);
        //velocity = glm::vec3(camera.forward / 90.0f);
    }

    if (sampleTimer.TimeSinceStarted() > 500.0f)
    {
        glm::vec3 pos = ball->GetPosition();
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
}
