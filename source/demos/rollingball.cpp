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
    terrainMesh = new Terrain();//("Assets/terrain.png");

    curve.controlPoints.push_back(glm::vec3(0,terrainMesh->GetHeightAt(0.0f,0.0f) + 0.15,0));
    curve.controlPoints.push_back(glm::vec3(0.5,terrainMesh->GetHeightAt(0.5f,1.0f) + 0.15,1));
    curve.controlPoints.push_back(glm::vec3(0,terrainMesh->GetHeightAt(0.0f,0.5f) + 0.15,0.5));
    curve.controlPoints.push_back(glm::vec3(1.5,terrainMesh->GetHeightAt(1.0f,0.0f) + 0.15,0));
    curve.controlPoints.push_back(glm::vec3(0,terrainMesh->GetHeightAt(0.0f,1.0f) + 0.15,1));
    curve.controlPoints.push_back(glm::vec3(0.5,terrainMesh->GetHeightAt(0.5f,1.0f) + 0.15,1));

    curve.degree = 3;

    curve.t = {
        0, 0, 0, 0, 0.25, 0.5, 0.75, 1, 1, 1, 1 //should match time-range/ interval in Update
        /*0, 0, 0, 0,       // first d+1 knots
        0.1, 0.2, 0.3,          // internal knots
        1, 1, 1*/          // last d+1 knots
    };

    GameObject* ball = new GameObject;
    ballMesh = new Mesh("Assets/Models/ball.obj");
    ball->AddComponent(ballMesh);
    ball->AddComponent(new SphereCollider());
    ballMesh->drawable->ubo.model = glm::scale(ballMesh->drawable->ubo.model, glm::vec3(0.1f,0.1f,0.1f));

    GameObject* terrain = new GameObject;
    ball->AddComponent(terrainMesh);
    ball->AddComponent(new TriangleCollider());

    camera.position = glm::vec3(0.0f, 0.0f, 4.0f);

    renderer->SetLightPos(glm::vec3(0,2,0));

    gameObjects.push_back(ball);
    gameObjects.push_back(terrain);

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    int j = 0;
    indices.push_back(j);
    for (float i = 0.0f; i < 1.0f; i += 0.01f)
    {
        j++;
        vertices.push_back(Vertex(curve.EvaluateBSplineSimple(i)));
        indices.push_back(j);
        indices.push_back(j);
    }

    splineDrawable = &renderer->CreateDrawable(vertices, indices, "shaders/color.vert.spv", "shaders/color.frag.spv", Renderer::LINES);
}

void RollingBall::Update()
{
    static float time = 0.0f;

    time += 0.001f;

    if (time > 1.0f)
    {
        time = 0.0f;
    }

    glm::vec3 pos = curve.EvaluateBSplineSimple(time);
    pos.y = terrainMesh->GetHeightAt(pos) + 0.1f;

    glm::mat4& matrix = ballMesh->drawable->ubo.model;
    matrix[3] = glm::vec4(pos, 1.0f);
}
