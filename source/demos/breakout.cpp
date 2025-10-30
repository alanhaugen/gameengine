#include "breakout.h"

Breakout::Breakout()
{
}

void Breakout::Init()
{
    audio->PlayMusic("Assets/Sounds/music.wav");

    background = new Sprite("Assets/Textures/background_2.png", -5, -5, 3.8, 5.6);

    //blocks.push_back(new Sprite(""));
}

void Breakout::Update()
{
}
