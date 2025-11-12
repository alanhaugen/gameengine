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
    ballMesh = new Mesh("Assets/Models/ball.obj");
    ballMesh->drawable->ubo.model = glm::scale(ballMesh->drawable->ubo.model, glm::vec3(0.1));

    terrainMesh = new Terrain("Assets/Textures/perlin.png");
    terrainMeshPoints = new Terrain("Assets/Textures/dovre.png", "shaders/color.vert.spv", "shaders/color.frag.spv", true);
    terrainMeshPoints->drawable->isVisible = false;

    camera.position = glm::vec3(0.0f, 0.0f, 4.0f);

    renderer->SetLightPos(glm::vec3(0,2,0));
}

void RollingBall::Update()
{
    if (input.Held(input.Key.SPACE))
    {
        glm::mat4& matrix = ballMesh->drawable->ubo.model;
        glm::vec3 pos = glm::vec3(matrix[3]);

        pos = glm::vec3(camera.position);
        matrix[3] = glm::vec4(pos, 1.0f);

        direction = glm::vec3(camera.forward / 90.0f);

        index++;
    }

    if (input.Held(input.Key.G))
    {
        terrainMeshPoints->drawable->isVisible = !terrainMeshPoints->drawable->isVisible;
        terrainMesh->drawable->isVisible = !terrainMesh->drawable->isVisible;
    }

    glm::mat4& matrix = ballMesh->drawable->ubo.model;
    glm::vec3 pos = glm::vec3(matrix[3]);

    direction += terrainMesh->GetNormal(pos);

    pos += direction;
    pos.y = terrainMesh->GetHeightAt(pos) + 0.1f;

    matrix[3] = glm::vec4(pos, 1.0f);
}
