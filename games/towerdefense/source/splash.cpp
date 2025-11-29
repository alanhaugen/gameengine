#include <core/platforms/application.h>
#include <iostream>
#include "splash.h"

void Splash::Init()
{
    GameObject* logo = new GameObject;
    Sprite* sprite = new Sprite("Assets/Textures/huldralogo.png");
    logo->AddComponent(sprite);

    float posX = renderer->windowWidth  / 2 - renderer->GetTextureWidth(sprite->drawable) / 2;
    float posY = renderer->windowHeight / 2 - renderer->GetTextureHeight(sprite->drawable) / 2;

    logo->SetPosition(glm::vec3(posX, posY, 0));

    renderer->SetClearColor(1,1,1);
    audio->PlaySound("Assets/Sounds/brick-hit-2.wav");

    timer.Start();
}

void Splash::Update(float deltaTime)
{
    if (timer.TimeSinceStarted() > 2000.0f)
    {
        Application::NextScene();
    }
}
