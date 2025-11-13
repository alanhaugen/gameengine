#include "empty.h"

Empty::Empty()
{
}

void Empty::Init()
{
    mesh = new Mesh("Assets/Models/ball.obj");
    //text = new Text("Game");
    //cube = new Cube();
}

void Empty::Update()
{
}

void Empty::Clean()
{
}
