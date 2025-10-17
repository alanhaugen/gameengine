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

    Text* score1;
    Text* score2;
};

#endif // PONG_H
