#include "vikingscene.h"
#include "glm/gtc/matrix_transform.hpp"

void VikingScene::Init()
{
    vikingCamp = new Mesh("../../Assets/Models/viking_room.obj", renderer);
    components.push_back(vikingCamp);
}

void VikingScene::Update(float time)
{
    vikingCamp->drawable->ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0,0,1));
}
