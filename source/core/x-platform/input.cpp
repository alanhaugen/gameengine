#include "input.h"

bool Input::Held(int key)
{
    return keys[key % KEYS];
}

bool Input::Released(int key)
{
    return keys[key % KEYS] == false && oldKeys[key % KEYS] == true;
}

bool Input::Pressed(int key)
{
    return keys[key % KEYS] == true && oldKeys[key % KEYS] == false;
}

bool Input::Init()
{
    mouse.Down = false;
    mouse.DownRight = false;
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

    return true;
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

    mouse.roll = 0.0f;
}

void Input::OnButton(const int button, const bool isDown)
{
    keys[button % KEYS] = isDown;
}
