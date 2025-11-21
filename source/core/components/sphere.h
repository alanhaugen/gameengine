#ifndef SPHERE_H
#define SPHERE_H

#include "visualobject.h"

class Sphere : public VisualObject
{
private:
    void GenerateIcoSphere(const char* vert, const char* frag);
    void GenerateUVSphere(const char* vert, const char* frag);
    void Init(const char* vert = "shaders/phong.vert.spv", const char* frag = "shaders/phong.frag.spv");

public:
    Sphere(float x, float y, float z, glm::vec3 scale = glm::vec3(1.0f));
    Sphere(glm::vec3 scale = glm::vec3(1.0f),
           glm::vec3 colour = glm::vec3(1.0f),
           const char* vertShader = "shaders/phong.vert.spv",
           const char* fragShader = "shaders/phong.frag.spv",
           bool instanced = false);
    void Update();
};

#endif // SPHERE_H
