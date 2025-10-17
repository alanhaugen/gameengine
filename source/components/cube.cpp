#include "cube.h"

Cube::Cube()
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

    renderer->CreateDrawable(vertices,
                             indices,
                             "shaders/shader.vert.spv",
                             "shaders/shader.frag.spv");
}


void Cube::Update()
{
}
