#include <core/platforms/application.h>
#include "splash.h"

void Splash::Init()
{
    logo = new Sprite("Assets/Textures/huldralogo.png");

    float posX = renderer->windowWidth / 2 - logo->drawable->textureWidth / 2;
    float posY = renderer->windowHeight / 2 - logo->drawable->textureHeight / 2;

    logo->SetPosition(glm::vec3(posX,posY,0));

    renderer->SetClearColor(1,1,1);
    audio->PlaySound("Assets/Sounds/brick-hit-2.wav");
}

void Splash::Update()
{
    i++;

    if (i > 200)
    {
        Application::NextScene();
    }
}

void Splash::Clean()
{
    delete logo;
}
