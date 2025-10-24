#include "vikingscene.h"
#include "glm/gtc/matrix_transform.hpp"

void VikingScene::Init()
{
    GameObject* first  = new GameObject;
    GameObject* second = new GameObject;
    vikingCamp = new Mesh("Assets/Models/viking_room.obj");
    ball = new Mesh("Assets/Models/ball.obj", "shaders/shader.vert.spv", "shaders/shader.frag.spv");

    camera.position = glm::vec3(.6,0,3);

    vikingCamp->Scale(glm::vec3(1.0, 1.0, 1.0));
    ball->Scale(glm::vec3(1.0, 1.0, 1.0));
    vikingCamp->Translate(glm::vec3(-0.3, 0, 0));
    ball->Translate(glm::vec3(1.7, 0, 0));

    first->AddComponent(vikingCamp);
    second->AddComponent(ball);
    gameObjects.push_back(first);
    gameObjects.push_back(second);
}

void VikingScene::Update()
{
    vikingCamp->Rotate(glm::radians(1.0f), glm::vec3(0,0,1));
    ball->Rotate(glm::radians(-1.0f), glm::vec3(0,0,1));
}
