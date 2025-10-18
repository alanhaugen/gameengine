#ifndef SPRITE_H
#define SPRITE_H

#include "component.h"

class Sprite : public Component
{
public:
    Sprite(const char* texture, float x = 0.0f, float y = 0.0f, const char* glyphs = "");
    void Update();

    Renderer::Drawable* drawable;
};

#endif // SPRITE_H
