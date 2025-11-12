#include "physicstestscene.h"
#include "../components/mesh.h"
#include "../components/terrain.h"
#include "../components/spherecollider.h"
#include "../components/cube.h"
#include <glm/gtc/matrix_transform.hpp>

PhysicsTestScene::PhysicsTestScene() {}


void PhysicsTestScene::Init()
{
    //Mesh* ballMeshC = new Mesh("Assets/Models/ball.obj");
    //Mesh* ballMeshD = new Mesh("Assets/Models/ball.obj");
    //Mesh* ballMeshE = new Mesh("Assets/Models/ball.obj");
    //Mesh* ballMeshF = new Mesh("Assets/Models/ball.obj");

    GameObject* colliderBallA = new GameObject("ballA");
    sphereCollider = new SphereCollider();
    Mesh* ballMeshA = new Mesh("Assets/Models/ball.obj");
    balls.push_back(ballMeshA);
    directions.push_back(glm::vec3());
    ballMeshA->drawable->ubo.model = glm::scale(ballMeshA->drawable->ubo.model,
                                                glm::vec3(0.5f,0.5f,0.5f));
    colliderBallA->AddComponent(ballMeshA);
    colliderBallA->AddComponent(sphereCollider);
    colliderBallA->mTransform.mPosition = glm::vec3{1.0f, 0.0f, 1.0f};

    GameObject* colliderBallB = new GameObject("ballB");
    Mesh* ballMeshB = new Mesh("Assets/Models/ball.obj");
    balls.push_back(ballMeshB);
    directions.push_back(glm::vec3());
    ballMeshB->drawable->ubo.model = glm::scale(ballMeshB->drawable->ubo.model, glm::vec3(0.5f,0.5f,0.5f));
    colliderBallB->AddComponent(ballMeshB);
    colliderBallB->AddComponent(sphereCollider);
    colliderBallB->mTransform.mPosition = glm::vec3{0.0f, 0.0f, 0.0f};

    wireframeCubeA = new Cube(-0.5f, 0.0f, -0.5f, glm::vec3{1.0f,1.0f,1.0f}, glm::vec3{1.0f,1.0f,1.0f});
    //cubeA->drawable->ubo.model = glm::scale(cubeA->drawable->ubo.model, glm::vec3(1.0f, 1.0f, 1.0f));
    //cubeA->mTransform.mPosition = glm::vec3{-0.5, 0.0f, 0.5f};

    camera.position = glm::vec3(0.0f, 0.0f, 10.0f);
    //camera.pitch = glm::vec3(0.0f, -30.0f, 0.0f);

    renderer->SetLightPos(glm::vec3(0,10,0));

    gameObjects.push_back(colliderBallA);
    qDebug() << "first ball pushed.";
    Log("first ball pushed.");
    gameObjects.push_back(colliderBallB);
    qDebug() << "second ball pushed.";
    Log("second ball pushed.");
    //gameObjects.push_back(terrain);
}

void PhysicsTestScene::Update()
{
    //Rotation
    wireframeCubeA->drawable->ubo.model = glm::rotate(wireframeCubeA->drawable->ubo.model,
                                                      glm::radians(1.0f), glm::vec3(0,1,0));

    //glm::mat4& matrix = ballMeshA->drawable->ubo.model;
    //glm::vec3 pos = glm::vec3(matrix[3]);
}
