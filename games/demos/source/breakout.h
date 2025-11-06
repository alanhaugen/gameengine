#ifndef BREAKOUT_H
#define BREAKOUT_H

#include "core/x-platform/scene.h"
#include "core/components/text.h"

const int NUMBER_OF_BLOCKS = 13 * 4;

class Breakout : public Scene
{
public:
    Breakout();
    void Init();
    void Update();

    Sprite* background;
    Sprite* paddle;

    std::vector<Sprite*> blocks;
    std::vector<Sprite*> balls;
    std::vector<glm::vec3> ballDirection;
};

#endif // BREAKOUT_H
