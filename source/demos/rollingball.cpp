#include "rollingball.h"
#include "../components/mesh.h"
#include "../components/terrain.h"
#include "../components/spherecollider.h"
#include "../components/trianglecollider.h"
#include <glm/gtc/matrix_transform.hpp>

RollingBall::RollingBall()
{
}

void RollingBall::Init()
{
    curve.controlPoints.push_back(glm::vec3(0,1,0));
    curve.controlPoints.push_back(glm::vec3(1,0,0));
    curve.controlPoints.push_back(glm::vec3(2,1,0));
    curve.controlPoints.push_back(glm::vec3(3,0,0));
    curve.controlPoints.push_back(glm::vec3(4,1,0));

    curve.t = {
        0, 0, 0,       // first d+1 knots
        1, 2,          // internal knots
        3, 3, 3          // last d+1 knots
    };

    GameObject* ball = new GameObject;
    ballMesh = new Mesh("Assets/Models/ball.obj");
    ball->AddComponent(ballMesh);
    ball->AddComponent(new SphereCollider());
    ballMesh->drawable->ubo.model = glm::scale(ballMesh->drawable->ubo.model, glm::vec3(0.1f,0.1f,0.1f));

    GameObject* terrain = new GameObject;
    ball->AddComponent(new Terrain("Assets/terrain.png"));
    ball->AddComponent(new TriangleCollider());

    camera.position = glm::vec3(0.0f, 0.0f, 4.0f);

    renderer->SetLightPos(glm::vec3(0,0,1));

    gameObjects.push_back(ball);
    gameObjects.push_back(terrain);
}

void RollingBall::Update()
{
    static float time = 0.0f;

    time += 0.01f;

    if (time > 3.0f)
    {
        time = 0.0f;
    }

    glm::mat4& matrix = ballMesh->drawable->ubo.model;
    //matrix[3] = glm::vec4(curve.EvaluateBSplineSimple(time), 1.0f);
}
