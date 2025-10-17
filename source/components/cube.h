#ifndef CUBE_H
#define CUBE_H

#include "component.h"

class Cube : public Component
{
public:
    Cube();

    void Update();

    Renderer::Drawable drawable;
};

#endif // CUBE_H
