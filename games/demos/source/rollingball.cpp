#include "rollingball.h"
#include "core/components/mesh.h"
#include "core/components/terrain.h"
#include <glm/gtc/matrix_transform.hpp>

RollingBall::RollingBall()
{
}

void RollingBall::Init()
{
    ballMesh = new Mesh("Assets/Models/ball.obj");
    ballMesh->Scale(0.1f);

    terrainMesh = new Terrain();//("Assets/blurred.png", "Assets/Textures/forrest_ground_01_diff_1k.jpg");//("Assets/terrain.png");

    camera.position = glm::vec3(0.0f, 150.0f, 0.0f);

    renderer->SetLightPos(glm::vec3(0,2,0));
}

void RollingBall::Update()
{
    glm::vec3 pos = ballMesh->GetPosition();

    if (input.Held(input.Key.SPACE))
    {
        pos = camera.position;
        velocity = glm::vec3(camera.forward / 90.0f);
    }

    velocity += terrainMesh->GetNormal(pos) / 5000.0f;

    pos += velocity;
    pos.y = terrainMesh->GetHeightAt(pos) + 0.1f;

    ballMesh->SetPosition(pos);
}

void RollingBall::Clean()
{
}
