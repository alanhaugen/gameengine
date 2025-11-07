#include "mainmenu.h"

void MainMenu::Init()
{
    audio->PlayMusic("Assets/Sounds/Caravan_mono.wav");

    terrain = new Terrain("Assets/HeightMaps/volcano3.png",
                          "Assets/Textures/forrest_ground_01_diff_1k.jpg",
                          "Shaders/phong.vert.spv", "Shaders/phong.frag.spv");

    terrain->SetPosition(glm::vec3(-50,-150,-50));
    renderer->SetLightPos(glm::vec3(-50, -150, -50));
}

void MainMenu::Update()
{

}

void MainMenu::Clean()
{
    delete terrain;
}
