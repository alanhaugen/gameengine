#ifndef BREAKOUT_H
#define BREAKOUT_H

#include "../x-platform/scene.h"
#include "../components/text.h"

class Breakout : public Scene
{
public:
    Breakout();
    void Init();
    void Update();

    Sprite* background;
};

#endif // BREAKOUT_H
