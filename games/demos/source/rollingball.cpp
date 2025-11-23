#include "rollingball.h"
#include "core/components/ballemitter.h"
#include "core/components/boxcollider.h"
#include "core/components/rigidbody.h"
#include "core/components/spherecollider.h"
#include "core/components/cube.h"
#include "core/components/trackingspline.h"

void RollingBall::Init()
{
    cube = new GameObject("Cube");
    cube->AddComponent(new Cube);
    cube->AddComponent(new BoxCollider(cube, Physics::STATIC));
    cube->SetPosition(320, 0, 500);

    terrain = new GameObject("Terrain");
    //terrainMeshPoints = new Terrain("Assets/PointClouds/snoehetta/output_smallest.txt", true);//("Assets/blurred.png", "Assets/Textures/forrest_ground_01_diff_1k.jpg");//("Assets/terrain.png");
    terrainMesh = new Terrain("tools/pointconverter/output.png", "Assets/Textures/snow.jpg");//("Assets/blurred.png", "Assets/Textures/forrest_ground_01_diff_1k.jpg");//("Assets/terrain.png");
    terrain->AddComponent(terrainMesh);

    particleSystem = new GameObject("Ball Particle Emitter");
    ballSystem = new BallEmitter(terrainMesh);
    particleSystem->AddComponent(ballSystem);
    particleSystem->SetPosition(300,300,500);

    ball = new GameObject("Ball");
    ball->AddComponent(new Sphere("Assets/Textures/orange.jpg"));
    ball->AddComponent(new TrackingSpline);
    ball->AddComponent(new SphereCollider(ball));
    ball->AddComponent(new RigidBody(terrainMesh));

    camera.position = glm::vec3(300.f, 300.0f, 500.0f);
}

void RollingBall::Update(float deltaTime)
{
    particleSystem->Update();

    cube->SetPosition(cube->GetPosition().x,
                      terrainMesh->GetHeightAt(cube->GetPosition()),
                      cube->GetPosition().z);

    if (input.Held(input.Key.R))
    {
        ballSystem->Reset();
        ball->SetPosition(camera.position);
    }
}
