#include "empty.h"

Empty::Empty()
{
}

void Empty::Init()
{
    cube = new Cube();
    cube->SetPosition(glm::vec3(0,0,-3));
    cube->Scale(0.1f);

    Cube* cube2 = new Cube();
    cube2->SetPosition(glm::vec3(-2,0,-3));
    cube2->Scale(0.1f);

    Cube* cube3 = new Cube();
    cube3->SetPosition(glm::vec3(-1,0,-3));
    cube3->Scale(0.1f);

    Cube* cube4 = new Cube();
    cube4->SetPosition(glm::vec3(0,1,-3));
    cube4->Scale(0.1f);
}

void Empty::Update()
{
}

void Empty::Clean()
{
}
