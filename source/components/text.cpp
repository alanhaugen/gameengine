#include "text.h"

Text::Text(const char *text, float x, float y, float z)
    : Sprite(x, y, text)
{
    textContent = text;
}
