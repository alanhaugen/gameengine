#ifndef BREAKOUT_H
#define BREAKOUT_H

#include "../x-platform/scene.h"
#include "../components/text.h"

const int NUMBER_OF_BLOCKS = 10;

class Breakout : public Scene
{
public:
    Breakout();
    void Init();
    void Update();

    Sprite* background;
    Sprite* paddle;

    std::vector<Sprite*> blocks;
};

#endif // BREAKOUT_H
