#ifndef SPLASH_H
#define SPLASH_H

#include <core/x-platform/scene.h>
#include <core/components/timer.h>
#include <core/components/sprite.h>

class Splash : public Scene
{
private:
    int i = 0;
    Timer timer;

public:
    void Init();
    void Update(float deltaTime);
};

#endif // SPLASH_H
