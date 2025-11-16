#ifndef SPLASH_H
#define SPLASH_H

#include <core/x-platform/timer.h>
#include <core/x-platform/scene.h>
#include <core/components/sprite.h>

class Splash : public Scene
{
private:
    Sprite* logo;
    int i = 0;
    Timer timer;

public:
    void Init();
    void Update();
    void Clean();
};

#endif // SPLASH_H
