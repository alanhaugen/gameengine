#include <core/platforms/application.h>
#include "vikingscene.h"
#include "glm/gtc/matrix_transform.hpp"
#include "core/components/gameobject.h"

void VikingScene::Init()
{
    GameObject* first  = new GameObject("Viking room");
    GameObject* second = new GameObject("Ball");
    vikingCamp = new Mesh("Assets/Models/viking_room.obj");
    ball = new Mesh("Assets/Models/ball.obj", "shaders/shader.vert.spv", "shaders/shader.frag.spv");

    //ballCollider = new SphereCollider();
    //first->AddComponent(ballCollider);

    audio->updateListener(glm::vec3(0.0f, 0.0f, 0.0f));
    music = audio->PlaySound("Music", "Assets/Audio/Caravan_mono.wav", true, 0.5f);
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
    if(input.Held(input.Key.SPACE))
    {
        Application::NextScene();
    }

    if(input.Held(input.Key.ESCAPE))
    {
        Application::Quit();
    }

    /*
    if(input.Held(input.Key.SPACE))
    {
        if(music->isPlaying)
        {
            music->Pause();
        }
        else
        {
            music->Play();
        }
    }

    if(input.Held(input.Key.W))
    {
        music->adjustGain(0.005f);
    }
    if(input.Held(input.Key.S))
    {
        music->adjustGain(-0.005f);
    }
    if(input.Held(input.Key.R))
    {
        music->adjustGain();
        //reset gain
    }*/

    vikingCamp->drawable->ubo.model = glm::rotate(vikingCamp->drawable->ubo.model, glm::radians(1.0f), glm::vec3(0,0,1));
    ball->drawable->ubo.model = glm::rotate(ball->drawable->ubo.model, glm::radians(-1.0f), glm::vec3(0,0,1));
}
