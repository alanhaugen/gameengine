#include "cube.h"
#include "core/components/gameobject.h"
#include "glm/gtc/matrix_transform.hpp"

void Cube::Init(glm::vec3 color)
{
    vertices.push_back(Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), color));
    vertices.push_back(Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), color));
    vertices.push_back(Vertex(glm::vec3( 1.0f, -1.0f, -1.0f), color));
    vertices.push_back(Vertex(glm::vec3( 1.0f, -1.0f, -1.0f), color));
    vertices.push_back(Vertex(glm::vec3( 1.0f,  1.0f, -1.0f), color));
    vertices.push_back(Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), color));

    vertices.push_back(Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), color));
    vertices.push_back(Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), color));
    vertices.push_back(Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), color));
    vertices.push_back(Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), color));
    vertices.push_back(Vertex(glm::vec3(-1.0f,  1.0f,  1.0f), color));
    vertices.push_back(Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), color));

    vertices.push_back(Vertex(glm::vec3(1.0f, -1.0f, -1.0f), color));
    vertices.push_back(Vertex(glm::vec3(1.0f, -1.0f,  1.0f), color));
    vertices.push_back(Vertex(glm::vec3(1.0f,  1.0f,  1.0f), color));
    vertices.push_back(Vertex(glm::vec3(1.0f,  1.0f,  1.0f), color));
    vertices.push_back(Vertex(glm::vec3(1.0f,  1.0f, -1.0f), color));
    vertices.push_back(Vertex(glm::vec3(1.0f, -1.0f, -1.0f), color));

    vertices.push_back(Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), color));
    vertices.push_back(Vertex(glm::vec3(-1.0f,  1.0f,  1.0f), color));
    vertices.push_back(Vertex(glm::vec3( 1.0f,  1.0f,  1.0f), color));
    vertices.push_back(Vertex(glm::vec3( 1.0f,  1.0f,  1.0f), color));
    vertices.push_back(Vertex(glm::vec3( 1.0f, -1.0f,  1.0f), color));
    vertices.push_back(Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), color));

    vertices.push_back(Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), color));
    vertices.push_back(Vertex(glm::vec3( 1.0f,  1.0f, -1.0f), color));
    vertices.push_back(Vertex(glm::vec3( 1.0f,  1.0f,  1.0f), color));
    vertices.push_back(Vertex(glm::vec3( 1.0f,  1.0f,  1.0f), color));
    vertices.push_back(Vertex(glm::vec3(-1.0f,  1.0f,  1.0f), color));
    vertices.push_back(Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), color));

    vertices.push_back(Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), color));
    vertices.push_back(Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), color));
    vertices.push_back(Vertex(glm::vec3( 1.0f, -1.0f, -1.0f), color));
    vertices.push_back(Vertex(glm::vec3( 1.0f, -1.0f, -1.0f), color));
    vertices.push_back(Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), color));
    vertices.push_back(Vertex(glm::vec3( 1.0f, -1.0f,  1.0f), color));
}

Cube::Cube(float x, float y, float z, glm::vec3 scale, glm::vec3 color)
{
    name = "Cube";

    Init(color);

    drawable = &renderer->CreateDrawable(vertices,
                                         indices,
                                         "shaders/color.vert.spv",
                                         "shaders/color.frag.spv",
                                         Renderer::TRIANGLES);

    glm::mat4& matrix = drawable->ubo.model;
    matrix = glm::translate(matrix, glm::vec3(glm::vec3(x, y, z)));
    matrix = glm::scale(matrix, scale);
}

void Cube::Update()
{
    if (gameObject)
    {
        drawable->ubo.model = gameObject->matrix;
    }
}
