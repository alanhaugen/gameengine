#include "wiredcube.h"

WiredCube::WiredCube(float x, float y, float z, glm::vec3 scale)
{
    name = "Wired Cube";
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    //for wireframe Cube
    vertices.push_back(Vertex(glm::vec3(-1.0f,   -1.0f,   -1.0f)));  //0
    vertices.push_back(Vertex(glm::vec3(-1.0f,   -1.0f,   1.0f)));  //1
    vertices.push_back(Vertex(glm::vec3(1.0f,   -1.0f,   1.0f)));  //2
    vertices.push_back(Vertex(glm::vec3(1.0f,   -1.0f,   -1.0f)));  //3

    vertices.push_back(Vertex(glm::vec3(-1.0f,   1.0f,   -1.0f)));  //4
    vertices.push_back(Vertex(glm::vec3(-1.0f,   1.0f,   1.0f)));  //5
    vertices.push_back(Vertex(glm::vec3(1.0f,   1.0f,   1.0f)));  //6
    vertices.push_back(Vertex(glm::vec3(1.0f,   1.0f,   -1.0f)));  //7

    //Bottom frame
    indices.push_back(0);indices.push_back(1);
    indices.push_back(1);indices.push_back(2);
    indices.push_back(2);indices.push_back(3);
    indices.push_back(3);indices.push_back(0);
    //Top frame
    indices.push_back(4);indices.push_back(5);
    indices.push_back(5);indices.push_back(6);
    indices.push_back(6);indices.push_back(7);
    indices.push_back(7);indices.push_back(4);
    //Vertical line
    indices.push_back(0);indices.push_back(4);
    indices.push_back(1);indices.push_back(5);
    indices.push_back(2);indices.push_back(6);
    indices.push_back(3);indices.push_back(7);

    drawable = renderer->CreateDrawable(vertices,
                                         indices,
                                         "shaders/color.vert.spv",
                                         "shaders/color.frag.spv",
                                         Renderer::LINES);

    renderer->Translate(drawable, glm::vec3(glm::vec3(x, y, z)));
    renderer->Scale(drawable, scale);
    //matrix = glm::translate(matrix, glm::vec3(glm::vec3(x, y, z)));
    //matrix = glm::scale(matrix, scale);
}

void WiredCube::Update()
{
}
