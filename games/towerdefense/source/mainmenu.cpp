#include "mainmenu.h"

void MainMenu::Init()
{
    audio->PlayMusic("Caravan_mono.wav");

    terrain = new Terrain("Assets/HeightMaps/volcano-0.png", "Assets/Textures/forrest_ground_01_diff_1k.jpg");
}

void MainMenu::Update()
{

}

void MainMenu::Clean()
{
    delete terrain;
}
