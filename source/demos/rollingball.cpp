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

    for (int i = 0; i < 500; i++)
    {
        Mesh* ballMesh = new Mesh("Assets/Models/ball.obj");
        balls.push_back(ballMesh);
        directions.push_back(glm::vec3());
        ballMesh->drawable->ubo.model = glm::scale(ballMesh->drawable->ubo.model, glm::vec3(0.1f,0.1f,0.1f));
        ball->AddComponent(ballMesh);
    }

    //ball->AddComponent(new SphereCollider());

    GameObject* terrain = new GameObject;
    terrainMesh = new Terrain("Assets/Pointclouds/island.txt");//("Assets/terrain.png");
    ball->AddComponent(terrainMesh);
    ball->AddComponent(new TriangleCollider());

    camera.position = glm::vec3(0.0f, 0.0f, 4.0f);

    renderer->SetLightPos(glm::vec3(0,2,0));

    gameObjects.push_back(ball);
    gameObjects.push_back(terrain);
}

void RollingBall::Update()
{
    if (input.Held(input.Key.SPACE))
    {
        glm::mat4& matrix = balls[index]->drawable->ubo.model;
        glm::vec3 pos = glm::vec3(matrix[3]);

        pos = glm::vec3(camera.position);
        matrix[3] = glm::vec4(pos, 1.0f);

        directions[index] = glm::vec3(camera.forward / 90.0f);

        index++;

        if (index > balls.size() - 1)
        {
            index = 0;
        }
    }

    for (int i = 0; i < balls.size(); i++)
    {
        glm::mat4& matrix = balls[i]->drawable->ubo.model;
        glm::vec3 pos = glm::vec3(matrix[3]);

        directions[i] += terrainMesh->GetNormal(pos) / 5000.0f;

        pos += directions[i];
        pos.y = terrainMesh->GetHeightAt(pos) + 0.1f;

        matrix[3] = glm::vec4(pos, 1.0f);
    }
}
