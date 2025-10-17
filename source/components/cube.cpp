#include "cube.h"
#include "glm/gtc/matrix_transform.hpp"

Cube::Cube(float x, float y, float z, glm::vec3 scale)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f, -10.0f)));
    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f, -10.0f)));
    vertices.push_back(Vertex(glm::vec3( 10.0f, -10.0f, -10.0f)));
    vertices.push_back(Vertex(glm::vec3( 10.0f, -10.0f, -10.0f)));
    vertices.push_back(Vertex(glm::vec3( 10.0f,  10.0f, -10.0f)));
    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f, -10.0f)));

    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f,  10.0f)));
    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f, -10.0f)));
    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f, -10.0f)));
    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f, -10.0f)));
    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f,  10.0f)));
    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f,  10.0f)));

    vertices.push_back(Vertex(glm::vec3(10.0f, -10.0f, -10.0f)));
    vertices.push_back(Vertex(glm::vec3(10.0f, -10.0f,  10.0f)));
    vertices.push_back(Vertex(glm::vec3(10.0f,  10.0f,  10.0f)));
    vertices.push_back(Vertex(glm::vec3(10.0f,  10.0f,  10.0f)));
    vertices.push_back(Vertex(glm::vec3(10.0f,  10.0f, -10.0f)));
    vertices.push_back(Vertex(glm::vec3(10.0f, -10.0f, -10.0f)));

    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f,  10.0f)));
    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f,  10.0f)));
    vertices.push_back(Vertex(glm::vec3( 10.0f,  10.0f,  10.0f)));
    vertices.push_back(Vertex(glm::vec3( 10.0f,  10.0f,  10.0f)));
    vertices.push_back(Vertex(glm::vec3( 10.0f, -10.0f,  10.0f)));
    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f,  10.0f)));

    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f, -10.0f)));
    vertices.push_back(Vertex(glm::vec3( 10.0f,  10.0f, -10.0f)));
    vertices.push_back(Vertex(glm::vec3( 10.0f,  10.0f,  10.0f)));
    vertices.push_back(Vertex(glm::vec3( 10.0f,  10.0f,  10.0f)));
    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f,  10.0f)));
    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f, -10.0f)));

    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f, -10.0f)));
    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f,  10.0f)));
    vertices.push_back(Vertex(glm::vec3( 10.0f, -10.0f, -10.0f)));
    vertices.push_back(Vertex(glm::vec3( 10.0f, -10.0f, -10.0f)));
    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f,  10.0f)));
    vertices.push_back(Vertex(glm::vec3( 10.0f, -10.0f,  10.0f)));

    drawable = &renderer->CreateDrawable(vertices,
                                         indices,
                                         "shaders/color.vert.spv",
                                         "shaders/color.frag.spv");

    glm::mat4& matrix = drawable->ubo.model;
    matrix = glm::translate(matrix, glm::vec3(glm::vec3(x, y, z)));
    matrix = glm::scale(matrix, scale);
}


void Cube::Update()
{
}
