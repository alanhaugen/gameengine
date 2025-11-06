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

    terrainMesh = new Terrain();//("Assets/terrain.png");

    camera.position = glm::vec3(0.0f, 0.0f, 4.0f);

    renderer->SetLightPos(glm::vec3(0,2,0));
}

void RollingBall::Update()
{
    glm::vec3 pos = ballMesh->GetPosition();

    if (input.Held(input.Key.SPACE))
    {
        pos = glm::vec3();
        velocity = glm::vec3();
    }

    velocity += glm::vec3();

    pos += velocity / 60.0f;
    pos.y = terrainMesh->GetHeightAt(pos) + 0.1f;

    ballMesh->SetPosition(pos);
}
