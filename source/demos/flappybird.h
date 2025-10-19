#ifndef FLAPPYBIRD_H
#define FLAPPYBIRD_H

#include "../x-platform/scene.h"
#include "../components/text.h"

class FlappyBird : public Scene
{
public:
    FlappyBird();
    void Init();
    void Update();

    Text* score;

    std::vector<Sprite*> pipes;

    Sprite* bird;
    Sprite* background;
    Sprite* ground;
};

#endif // FLAPPYBIRD_H
