#ifndef PONG_H
#define PONG_H

#include "../x-platform/scene.h"
#include "../components/sphere.h"
#include "../components/cube.h"
#include "../components/text.h"

class Pong : public Scene
{
public:
    Pong();
    void Init();
    void Update();

    Sphere* ball;
    Cube* paddle1;
    Cube* paddle2;

    glm::vec3 direction;
    bool goRight = true;

    Text* score1;
    Text* score2;

    int playerOneScore = 0;
    int playerTwoScore = 0;
};

#endif // PONG_H
