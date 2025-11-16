#ifndef PONG_H
#define PONG_H

#include "core/x-platform/scene.h"
#include "core/components/sphere.h"
#include "core/components/cube.h"
#include "core/components/text.h"
#include "core/components/wiredcube.h"

class Pong : public Scene
{
private:
    Sphere* ball;
    Cube* paddle1;
    Cube* paddle2;

    glm::vec3 direction;
    bool goRight = true;

    Text* score1;
    Text* score2;

    int playerOneScore = 0;
    int playerTwoScore = 0;

    enum state
    {
        PLAYING,
        START,
        WIN,
        WAIT
    };

    int state = START;

    Text* instructions1;
    Text* instructions2;

    Text* win1;
    Text* win2;

public:
    Pong();
    void Init();
    void Update();
};

#endif // PONG_H
