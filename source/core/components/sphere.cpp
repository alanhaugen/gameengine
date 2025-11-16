#include "sphere.h"
#include "glm/gtc/matrix_transform.hpp"

Sphere::Sphere(float x, float y, float z, glm::vec3 scale)
    : Mesh("Assets/Models/ball.obj", "shaders/color.vert.spv", "shaders/color.frag.spv")
{
    name = "Sphere";
    glm::mat4& matrix = drawable->ubo.model;
    matrix = glm::translate(matrix, glm::vec3(x, y, z));
    matrix = glm::scale(matrix, scale);
}

Sphere::Sphere(glm::vec3 scale)
    : Mesh("Assets/Models/ball.obj", "shaders/color.vert.spv", "shaders/color.frag.spv")
{
    name = "Sphere";
    glm::mat4& matrix = drawable->ubo.model;
    matrix = glm::scale(matrix, scale);
}
