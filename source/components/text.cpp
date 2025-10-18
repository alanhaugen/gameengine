#include "text.h"

Text::Text(const char *text, float x, float y, float z)
    : Sprite("Assets/Textures/sheetWhite.png",x, y, text)
{
    textContent = text;
}
