#include <core/platforms/application.h>
#include "vikingscene.h"
#include "core/components/gameobject.h"

void VikingScene::Init()
{
    first  = new GameObject("Viking room");
    first->AddComponent(new Mesh("Assets/Models/viking_room.obj"));

    second = new GameObject("Ball");
    second->AddComponent(new Mesh("Assets/Models/ball.obj", "shaders/shader.vert.spv", "shaders/shader.frag.spv"));

    camera.position = glm::vec3(.6,0,3);

    first->Scale(glm::vec3(1.0, 1.0, 1.0));
    second->Scale(glm::vec3(1.0, 1.0, 1.0));
    first->Translate(glm::vec3(-0.3, 0, 0));
    second->Translate(glm::vec3(1.7, 0, 0));
}

void VikingScene::Update()
{
    if(input.Held(input.Key.SPACE))
    {
        Application::NextScene();
    }

    if(input.Held(input.Key.ESCAPE))
    {
        Application::Quit();
    }

    first->Rotate(glm::radians(1.0f), glm::vec3(0,0,1));
    second->Rotate(glm::radians(-1.0f), glm::vec3(0,0,1));
}
