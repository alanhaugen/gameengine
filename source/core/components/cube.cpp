#include "cube.h"
#include "core/components/gameobject.h"

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

    drawable = renderer->CreateDrawable(vertices,
                                         indices,
                                         "shaders/color.vert.spv",
                                         "shaders/color.frag.spv",
                                         Renderer::TRIANGLES);

    renderer->Translate(drawable, glm::vec3(glm::vec3(x, y, z)));
    renderer->Scale(drawable, scale);
}

void Cube::Update(float deltaTime)
{
    if (gameObject)
    {
        renderer->SetModel(drawable, gameObject->matrix);
    }
}
