#include "input.h"
#include "locator.h"

bool Input::Held(int key)
{
    return keys[key];
}

bool Input::Released(int key)
{
    return keys[key] == false && oldKeys[key] == true;
}

bool Input::Pressed(int key)
{
    return keys[key] == true && oldKeys[key] == false;
}

void Input::Init()
{
    mouse.Down = false;
    mouse.x = 0;
    mouse.y = 0;
    mouse.xOld = 0;
    mouse.yOld = 0;
    mouse.dx = 0;
    mouse.dy = 0;

    for (int i = 0; i < KEYS; i++)
    {
        keys[i] = false;
    }
}

void Input::Update()
{
    for (int i = 0; i < KEYS; i++)
    {
        oldKeys[i] = keys[i];
    }

    mouse.dx = mouse.x - mouse.xOld;
    mouse.dy = mouse.y - mouse.yOld;

    mouse.xOld = mouse.x;
    mouse.yOld = mouse.y;
}

void Input::OnButton(const unsigned int button, const bool isDown)
{
    keys[button % KEYS] = isDown;
}
