#include "vikingscene.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../components/gameobject.h"

void VikingScene::Init()
{
    GameObject* first  = new GameObject("Viking room 1");
    GameObject* second = new GameObject("Viking room 2");
    vikingCamp = new Mesh("Assets/Models/viking_room.obj");
    ball = new Mesh("Assets/Models/ball.obj", "shaders/shader.vert.spv", "shaders/shader.frag.spv");

    camera.position = glm::vec3(.6,0,3);

    ball->drawable->ubo.modelMat = glm::mat4(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
    ball->drawable->ubo.normalMat = glm::mat4(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);

    vikingCamp->drawable->ubo.model = glm::scale(vikingCamp->drawable->ubo.model, glm::vec3(1.0, 1.0, 1.0));
    ball->drawable->ubo.model = glm::scale(ball->drawable->ubo.model, glm::vec3(1.0, 1.0, 1.0));
    vikingCamp->drawable->ubo.model = glm::translate(vikingCamp->drawable->ubo.model, glm::vec3(-0.3, 0, 0));
    ball->drawable->ubo.model = glm::translate(ball->drawable->ubo.model, glm::vec3(1.7, 0, 0));

    first->AddComponent(vikingCamp);
    second->AddComponent(ball);
    gameObjects.push_back(first);
    gameObjects.push_back(second);
}

void VikingScene::Update()
{
    vikingCamp->drawable->ubo.model = glm::rotate(vikingCamp->drawable->ubo.model, glm::radians(1.0f), glm::vec3(0,0,1));
    ball->drawable->ubo.model = glm::rotate(ball->drawable->ubo.model, glm::radians(-1.0f), glm::vec3(0,0,1));
}
