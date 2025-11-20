#ifndef SPHERE_H
#define SPHERE_H

#include "mesh.h"

class Sphere : public Mesh
{
public:
    Sphere(float x, float y, float z, glm::vec3 scale = glm::vec3(1.0f));
    Sphere(glm::vec3 scale = glm::vec3(1.0f),
           glm::vec3 colour = glm::vec3(1.0f),
           const char* vertShader = "shaders/phong.vert.spv",
           const char* fragShader = "shaders/phong.frag.spv");
};

#endif // SPHERE_H
