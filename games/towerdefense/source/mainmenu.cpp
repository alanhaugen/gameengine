#include "mainmenu.h"

void MainMenu::Init()
{
    audio->PlayMusic("Assets/Sounds/Caravan_mono.wav");

    terrain = new Terrain("Assets/HeightMaps/volcano05.png",
                          "Assets/Textures/aerial_rocks_04_diff_1k.jpg",
                          "Shaders/phong.vert.spv", "Shaders/phong.frag.spv");

    terrain->SetPosition(glm::vec3(-50,-280,-50));
    terrain->Scale(glm::vec3(1,2,1));
    renderer->SetLightPos(glm::vec3(-50, -150, -50));

    mountainsNorth = new Terrain("Assets/HeightMaps/volcano01.png",
                          "Assets/Textures/forrest_ground_01_diff_1k.jpg",
                          "Shaders/phong.vert.spv", "Shaders/phong.frag.spv");
    mountainsNorth->SetPosition(glm::vec3(-1050,-150,970));
    mountainsNorth->Scale(glm::vec3(3,1,1));
    mountainsEast = new Terrain("Assets/HeightMaps/volcano02.png",
                          "Assets/Textures/forrest_ground_01_diff_1k.jpg",
                          "Shaders/phong.vert.spv", "Shaders/phong.frag.spv");
    mountainsEast->SetPosition(glm::vec3(970,-150,-50));
    mountainsSouth = new Terrain("Assets/HeightMaps/volcano03.png",
                          "Assets/Textures/forrest_ground_01_diff_1k.jpg",
                          "Shaders/phong.vert.spv", "Shaders/phong.frag.spv");
    mountainsSouth->SetPosition(glm::vec3(-1050,-150,-1050));
    mountainsSouth->Scale(glm::vec3(3,1,1));
    mountainsWest = new Terrain("Assets/HeightMaps/volcano04.png",
                          "Assets/Textures/forrest_ground_01_diff_1k.jpg",
                          "Shaders/phong.vert.spv", "Shaders/phong.frag.spv");
    mountainsWest->SetPosition(glm::vec3(-1050,-150,-50));

    logo = new Sprite("Assets/Textures/towerofpowerlogo.png", 0, 0, 0.3, 0.3);
    playGameButton = new Sprite("Assets/Textures/playTowerDefenseButton.png", 0, 0, 0.2, 0.2);
    //quitGameButton = new Sprite("Assets/Textures/quitTowerDefenseButton.png", 0, 0, 0.3, 0.3);
    float logoOffsetX = ((renderer->windowWidth / 2) - (logo->drawable->textureWidth * 0.3) / 2);
    logo->SetPosition(glm::vec3(logoOffsetX, 0, 0));
    float playButtonOffsetX = ((renderer->windowWidth / 2) - (playGameButton->drawable->textureWidth * 0.2) / 2);
    playGameButton->SetPosition(glm::vec3(playButtonOffsetX, 300, 0));
}

void MainMenu::Update()
{
    if (playGameButton->IsPressed())
    {
        logo->drawable->isVisible = false;
        playGameButton->drawable->isVisible = false;
        //quitGameButton->drawable->isVisible = false;
    }

}

void MainMenu::Clean()
{
    delete terrain;
}
