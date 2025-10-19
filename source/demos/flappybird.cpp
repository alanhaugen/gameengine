#include "flappybird.h"

FlappyBird::FlappyBird()
{
}

void FlappyBird::Init()
{
    score = new Text("Score: 0");

    bird = new Sprite("Assets/Textures/bird.png", 50, 50);
    background = new Sprite("Assets/Textures/background.png");
    ground = new Sprite("Assets/Textures/ground.png",0, 100);

    audio->PlayMusic("Assets/Sounds/marios_way.mp3");
}

void FlappyBird::Update()
{
}
