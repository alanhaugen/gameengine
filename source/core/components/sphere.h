#ifndef SPHERE_H
#define SPHERE_H

#include "visualobject.h"

class Sphere : public VisualObject
{
private:
    void GenerateIcoSphere(const char* vert, const char* frag, const char* texture);
    void GenerateUVSphere(const char* vert, const char* frag, const char* texture);
    void Init(const char* vert = "shaders/color.vert.spv",
              const char* frag = "shaders/color.frag.spv",
              const char* texture = "");

    bool isInstanced = false;

public:
    Sphere(const char* texture);
    Sphere(float x, float y, float z, glm::vec3 scale = glm::vec3(1.0f));
    Sphere(glm::vec3 scale = glm::vec3(1.0f),
           glm::vec3 colour = glm::vec3(1.0f),
           const char* vertShader = "shaders/color.vert.spv",
           const char* fragShader = "shaders/color.frag.spv",
           bool instanced = false);
    void Update(float deltaTime);
};

#endif // SPHERE_H
