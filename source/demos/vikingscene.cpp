#include "vikingscene.h"
#include "glm/gtc/matrix_transform.hpp"

void VikingScene::Init()
{
    vikingCamp = new Mesh("Assets/Models/viking_room.obj");
    components.push_back(vikingCamp);
}

void VikingScene::Update(float time)
{
    glm::rotate(vikingCamp->matrix, time * glm::radians(90.0f), glm::vec3(0,1,0));
}
