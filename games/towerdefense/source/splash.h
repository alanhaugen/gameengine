#ifndef SPLASH_H
#define SPLASH_H

#include "core/x-platform/scene.h"
#include "core/components/sprite.h"

class Splash : public Scene
{
private:
    Sprite* logo;

public:
    void Init();
    void Update();
};

#endif // SPLASH_H
