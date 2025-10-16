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
    GameObject* ball = new GameObject;
    ballMesh = new Mesh("Assets/Models/ball.obj");
    ball->AddComponent(ballMesh);
    ball->AddComponent(new SphereCollider());
    ballMesh->drawable->ubo.model = glm::scale(ballMesh->drawable->ubo.model, glm::vec3(0.1f,0.1f,0.1f));

    GameObject* terrain = new GameObject;
    terrainMesh = new Terrain();//("Assets/terrain.png");
    ball->AddComponent(terrainMesh);
    ball->AddComponent(new TriangleCollider());

    camera.position = glm::vec3(0.0f, 0.0f, 4.0f);

    renderer->SetLightPos(glm::vec3(0,2,0));

    gameObjects.push_back(ball);
    gameObjects.push_back(terrain);
}

void RollingBall::Update()
{
    glm::mat4& matrix = ballMesh->drawable->ubo.model;
    glm::vec3 pos = glm::vec3(matrix[3]);

    if (input.Held(input.Key.SPACE))
    {
        pos = glm::vec3(0,0,0);
        direction = glm::vec3(0,0,0);
    }

    direction += terrainMesh->GetNormal(pos) / 5000.0f;

    pos += direction;
    pos.y = terrainMesh->GetHeightAt(pos) + 0.1f;

    matrix[3] = glm::vec4(pos, 1.0f);
}
