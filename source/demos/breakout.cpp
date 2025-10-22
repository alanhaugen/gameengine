#include "breakout.h"

Breakout::Breakout()
{
}

void Breakout::Init()
{
    audio->PlayMusic("Assets/Sounds/music.wav");

    float x = 0.0f;
    float y = 0.0f;
    for (int i = 0; i < NUMBER_OF_BLOCKS; i++)
    {
        x += 50.0f;

        blocks.push_back(new Sprite("Assets/Textures/blocks.png", x, y, 2.0f, 2.0f, 33,15));

        if (i % 5 == 0)
        {
            y += 10.0f;
            x = 0;
        }
    }

    paddle = new Sprite("Assets/Textures/blocks.png", 100, 100, 1, 1, 128, 16);
    paddle->drawable->ubo.index.x = 6;

    background = new Sprite("Assets/Textures/background_2.png", -5, -5, 3.8, 5.6);
}

void Breakout::Update()
{
}
