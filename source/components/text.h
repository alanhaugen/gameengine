#ifndef TEXT_H
#define TEXT_H

#include "sprite.h"

class Text : public Sprite
{
public:
    Text(const char* text, float x = 0.0f, float y = 0.0f, float z = 0.0f);
};

#endif // TEXT_H
