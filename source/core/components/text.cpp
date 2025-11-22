#include "text.h"

Text::Text(const char *text, float x, float y, float z)
    : Sprite("Assets/Textures/sheetWhite.png", x, y, 1.0f, 1.0f, 64, 64, text)
{
    name = "Text";
    textContent = text;
}

void Text::ChangeText(const char *text)
{

}
