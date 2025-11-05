#include "vikingscene.h"
#include "glm/gtc/matrix_transform.hpp"

void VikingScene::Init()
{
    GameObject* first = new GameObject("Viking1");
    GameObject* second = new GameObject("Viking2");
    vikingCamp1 = new Mesh("Assets/Models/viking_room.obj");
    vikingCamp2 = new Mesh("Assets/Models/viking_room.obj", "shaders/shader.vert.spv", "shaders/shader.frag.spv");

    audio->updateListener(glm::vec3(0.0f, 0.0f, 0.0f));
    Music = audio->PlaySound("Music", "Assets/Audio/Caravan_mono.wav", true, 0.5f);

    camera.position += glm::vec3(.6,0,3);

    //vikingCamp2->drawable->ubo.modelMat = glm::mat4(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
    //vikingCamp2->drawable->ubo.normalMat = glm::mat4(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);

    vikingCamp2->drawable->ubo.cameraPosition = glm::vec3(10,1,0);
    vikingCamp2->drawable->ubo.lightPosition = glm::vec3(1,1,0);

    vikingCamp1->drawable->ubo.model = glm::scale(vikingCamp1->drawable->ubo.model, glm::vec3(1.0, 1.0, 1.0));
    vikingCamp2->drawable->ubo.model = glm::scale(vikingCamp2->drawable->ubo.model, glm::vec3(1.0, 1.0, 1.0));
    vikingCamp1->drawable->ubo.model = glm::translate(vikingCamp1->drawable->ubo.model, glm::vec3(-0.3, 0, 0));
    vikingCamp2->drawable->ubo.model = glm::translate(vikingCamp2->drawable->ubo.model, glm::vec3(1.7, 0, 0));

    first->AddComponent(vikingCamp1);
    second->AddComponent(vikingCamp2);
    gameObjects.push_back(first);
    gameObjects.push_back(second);





}

void VikingScene::Update()
{
    if(input.Held(input.Key.SPACE))
    {
        if(Music->isPlaying)
        {
            Music->Pause();
        }
        else
        {
            Music->Play();
        }
    }

    if(input.Held(input.Key.W))
    {
        Music->adjustGain(0.005f);
    }
    if(input.Held(input.Key.S))
    {
        Music->adjustGain(-0.005f);
    }
    if(input.Held(input.Key.R))
    {
        Music->adjustGain();
        //reset gain
    }

    vikingCamp1->drawable->ubo.model = glm::rotate(vikingCamp1->drawable->ubo.model, glm::radians(1.0f), glm::vec3(0,0,1));
    vikingCamp2->drawable->ubo.model = glm::rotate(vikingCamp2->drawable->ubo.model, glm::radians(-1.0f), glm::vec3(0,0,1));
}
