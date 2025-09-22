#include "vikingscene.h"
#include "glm/gtc/matrix_transform.hpp"

void VikingScene::Init()
{
    vikingCamp1 = new Mesh("Assets/Models/viking_room.obj", renderer);
    vikingCamp2 = new Mesh("Assets/Models/viking_room.obj", renderer, "shaders/phong.vert.spv", "shaders/phong.frag.spv");

    vikingCamp2->drawable->ubo.colour = glm::vec4(1,1,1,1);
    //vikingCamp2->drawable->ubo.modelMat = glm::mat4(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
    //vikingCamp2->drawable->ubo.normalMat = glm::mat4(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);

    vikingCamp2->drawable->ubo.cameraPosition = glm::vec4(10,1,0,1);
    vikingCamp2->drawable->ubo.lightPosition = glm::vec4(1,1,0,1);

    vikingCamp1->drawable->ubo.model = glm::scale(vikingCamp1->drawable->ubo.model, glm::vec3(0.4, 0.4, 0.4));
    vikingCamp2->drawable->ubo.model = glm::scale(vikingCamp2->drawable->ubo.model, glm::vec3(0.4, 0.4, 0.4));
    vikingCamp1->drawable->ubo.model = glm::translate(vikingCamp1->drawable->ubo.model, glm::vec3(-0.3, 0, 0));
    vikingCamp2->drawable->ubo.model = glm::translate(vikingCamp2->drawable->ubo.model, glm::vec3(1.7, 0, 0));
    components.push_back(vikingCamp1);
    components.push_back(vikingCamp2);
}

void VikingScene::Update()
{
    vikingCamp1->drawable->ubo.model = glm::rotate(vikingCamp1->drawable->ubo.model, glm::radians(1.0f), glm::vec3(0,0,1));
    vikingCamp2->drawable->ubo.model = glm::rotate(vikingCamp2->drawable->ubo.model, glm::radians(-1.0f), glm::vec3(0,0,1));
}
