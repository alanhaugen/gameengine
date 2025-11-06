#ifndef FLAPPYBIRD_H
#define FLAPPYBIRD_H

#include "../x-platform/scene.h"
#include "../components/text.h"

const int MAX_SCORE = 100;

class FlappyBird : public Scene
{
public:
    FlappyBird();
    void Init();
    void Update();

    std::vector<Text*> scores;
    Text* score;
    int playerScore = 0;

    std::vector<Sprite*> pipes;

    Sprite* bird;
    Sprite* background;
    Sprite* ground;

    bool jumped = false;
    float force = 0.0f;
    glm::vec4 startPos;

    Text* instructions;

    bool isGiveScore = true;

    enum
    {
        PLAYING,
        START
    };

    int state = START;
};

#endif // FLAPPYBIRD_H
