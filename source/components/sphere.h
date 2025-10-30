#ifndef SPHERE_H
#define SPHERE_H

#include "mesh.h"

class Sphere : public Mesh
{
public:
    Sphere(float x, float y, float z, glm::vec3 scale = glm::vec3(1.0f));
};

#endif // SPHERE_H
