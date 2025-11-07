#ifndef MAINMENU_H
#define MAINMENU_H

#include <core/components/terrain.h>
#include <core/x-platform/scene.h>

class MainMenu : public Scene
{
private:
    Terrain* terrain;

public:
    void Init();
    void Update();
    void Clean();
};

#endif
