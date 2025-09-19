#include "vikingscene.h"
#include "../components/mesh.h"

void VikingScene::Init()
{
    components.push_back(new Mesh("Assets/Models/viking_room.obj"));
}

void VikingScene::Update()
{
}
