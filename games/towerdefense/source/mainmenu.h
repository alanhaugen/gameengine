#ifndef MAINMENU_H
#define MAINMENU_H

#include <core/components/sprite.h>
#include <core/components/terrain.h>
#include <core/components/sphere.h>
#include <core/x-platform/scene.h>

class MainMenu : public Scene
{
private:
    Terrain* terrain;
    Sprite* logo;
    Sprite* playGameButton;
    Sprite* quitGameButton;

    Terrain* mountainsNorth;
    Terrain* mountainsEast;
    Terrain* mountainsSouth;
    Terrain* mountainsWest;

    Sphere* ball;
    glm::vec3 velocity;
    glm::vec3 pos;

public:
    void Init();
    void Update();
    void Clean();
};

#endif
