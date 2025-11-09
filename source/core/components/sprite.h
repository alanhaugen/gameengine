#ifndef SPRITE_H
#define SPRITE_H

#include "visualobject.h"

class Sprite : public VisualObject
{
public:
    Sprite(const char* texture, float x = 0.0f, float y = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f, int width = 0, int height = 0, const char* glyphs = "");
    bool IsPressed();
    void Update();
};

#endif // SPRITE_H
