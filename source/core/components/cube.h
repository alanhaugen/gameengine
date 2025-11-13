#ifndef CUBE_H
#define CUBE_H

#include "visualobject.h"

class Cube : public VisualObject
{
public:
    Cube(float x = 0.0f,
         float y = 0.0f,
         float z = 0.0f,
         glm::vec3 scale = glm::vec3(0.1f),
         glm::vec3 color = glm::vec3(1.0f));

    void Update();
};

#endif // CUBE_H
