#ifndef GAME_H
#define GAME_H

#include "core/x-platform/scene.h"

class Game : public Scene
{
    void Init();
    void Update(float deltaTime);
};

#endif
