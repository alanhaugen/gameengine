#ifndef WIREDCUBE_H
#define WIREDCUBE_H

#include "visualobject.h"

class WiredCube : public VisualObject
{
public:
    WiredCube(float x = 0.0f,
              float y = 0.0f,
              float z = 0.0f,
              glm::vec3 scale = glm::vec3(1.0f));
private:
    void Update();
};

#endif // WIREDCUBE_H
