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
    ballMesh = new Mesh("Assets/Models/ball.obj");

    //terrainMesh = new Terrain("Assets/PointClouds/snoehetta/output_smallest.txt", true);//("Assets/blurred.png", "Assets/Textures/forrest_ground_01_diff_1k.jpg");//("Assets/terrain.png");
    terrainMesh = new Terrain("tools/pointconverter/output.png", "Assets/Textures/snow.jpg");//("Assets/blurred.png", "Assets/Textures/forrest_ground_01_diff_1k.jpg");//("Assets/terrain.png");

    camera.position = glm::vec3(0.0f, 0.0f, 4.0f);
}

void RollingBall::Update(float deltaTime)
{
    glm::vec3 pos = ballMesh->GetPosition();

    if (input.Held(input.Key.R))
    {
        pos = camera.position;
        velocity = glm::vec3(camera.forward / 90.0f);
    }

    /*if (input.Held(input.Key.SPACE))
    {
        Application::NextScene();
    }*/

    velocity += terrainMesh->GetNormal(pos) / 500.0f;
    velocity -= velocity * frictionCoeff * deltaTime;

    if (velocity.length() <= (1.0f))
    {
        velocity = glm::vec3(0.0f);
    }

    pos += velocity;
    pos.y = terrainMesh->GetHeightAt(pos) + 1.0f;

    ballMesh->SetPosition(pos);
}
