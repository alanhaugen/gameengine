#ifndef SPRITE_H
#define SPRITE_H

#include "component.h"

class Sprite : public Component
{
public:
    Sprite();
    void Update();

    Renderer::Drawable* drawable;
};

#endif // SPRITE_H
