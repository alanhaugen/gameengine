#include "rollingball.h"
#include "../components/mesh.h"
#include "../components/terrain.h"
#include "../components/spherecollider.h"
#include "../components/trianglecollider.h"
#include "../components/fpscamera.h"
#include <glm/gtc/matrix_transform.hpp>

RollingBall::RollingBall()
{
}

void RollingBall::Init()
{
    GameObject* ball = new GameObject;
    ballMesh = new Mesh("Assets/Models/ball.obj", "shaders/phong.vert.spv", "shaders/phong.frag.spv");
    ball->AddComponent(ballMesh);
    ball->AddComponent(new SphereCollider());
    ball->AddComponent(new FPSCamera(&camera));

    GameObject* terrain = new GameObject;
    ball->AddComponent(new Terrain("Assets/terrain.png"));
    ball->AddComponent(new TriangleCollider());

    renderer->SetCameraPosition(glm::vec3(0,10.0f,0));

    gameObjects.push_back(ball);
    gameObjects.push_back(terrain);
}

void RollingBall::Update()
{
    glm::mat4& matrix = ballMesh->drawable->ubo.model;
    matrix = glm::translate(matrix, glm::vec3(0,force,0));

    force -= 0.000098f;

    if (matrix[3].y < -1.0f)
    {
        force = 0.01f;
    }
}
