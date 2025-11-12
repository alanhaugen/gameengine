#include "cube.h"
#include "glm/gtc/matrix_transform.hpp"

void Cube::Init()
{
    //for wireframe Cube
    vertices.push_back(Vertex(glm::vec3(0.0f,   0.0f,   0.0f)));    //0
    vertices.push_back(Vertex(glm::vec3(0.0f,   0.0f,   1.0f)));   //1
    vertices.push_back(Vertex(glm::vec3(1.0f,   0.0f,   1.0f)));   //2
    vertices.push_back(Vertex(glm::vec3(1.0f,   0.0f,   0.0f)));  //3

    vertices.push_back(Vertex(glm::vec3(0.0f,   1.0f,   0.0f)));   //4
    vertices.push_back(Vertex(glm::vec3(0.0f,   1.0f,   1.0f)));  //5
    vertices.push_back(Vertex(glm::vec3(1.0f,   1.0f,   1.0f)));  //6
    vertices.push_back(Vertex(glm::vec3(1.0f,   1.0f,   0.0f))); //7

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

    /*
    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f, -10.0f), color));
    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f, -10.0f), color));
    vertices.push_back(Vertex(glm::vec3( 10.0f, -10.0f, -10.0f), color));
    vertices.push_back(Vertex(glm::vec3( 10.0f, -10.0f, -10.0f), color));
    vertices.push_back(Vertex(glm::vec3( 10.0f,  10.0f, -10.0f), color));
    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f, -10.0f), color));

    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f,  10.0f), color));
    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f, -10.0f), color));
    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f, -10.0f), color));
    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f, -10.0f), color));
    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f,  10.0f), color));
    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f,  10.0f), color));

    vertices.push_back(Vertex(glm::vec3(10.0f, -10.0f, -10.0f), color));
    vertices.push_back(Vertex(glm::vec3(10.0f, -10.0f,  10.0f), color));
    vertices.push_back(Vertex(glm::vec3(10.0f,  10.0f,  10.0f), color));
    vertices.push_back(Vertex(glm::vec3(10.0f,  10.0f,  10.0f), color));
    vertices.push_back(Vertex(glm::vec3(10.0f,  10.0f, -10.0f), color));
    vertices.push_back(Vertex(glm::vec3(10.0f, -10.0f, -10.0f), color));

    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f,  10.0f), color));
    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f,  10.0f), color));
    vertices.push_back(Vertex(glm::vec3( 10.0f,  10.0f,  10.0f), color));
    vertices.push_back(Vertex(glm::vec3( 10.0f,  10.0f,  10.0f), color));
    vertices.push_back(Vertex(glm::vec3( 10.0f, -10.0f,  10.0f), color));
    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f,  10.0f), color));

    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f, -10.0f), color));
    vertices.push_back(Vertex(glm::vec3( 10.0f,  10.0f, -10.0f), color));
    vertices.push_back(Vertex(glm::vec3( 10.0f,  10.0f,  10.0f), color));
    vertices.push_back(Vertex(glm::vec3( 10.0f,  10.0f,  10.0f), color));
    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f,  10.0f), color));
    vertices.push_back(Vertex(glm::vec3(-10.0f,  10.0f, -10.0f), color));

    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f, -10.0f), color));
    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f,  10.0f), color));
    vertices.push_back(Vertex(glm::vec3( 10.0f, -10.0f, -10.0f), color));
    vertices.push_back(Vertex(glm::vec3( 10.0f, -10.0f, -10.0f), color));
    vertices.push_back(Vertex(glm::vec3(-10.0f, -10.0f,  10.0f), color));
    vertices.push_back(Vertex(glm::vec3( 10.0f, -10.0f,  10.0f), color));
    */
}

Cube::Cube(float x, float y, float z, glm::vec3 scale, glm::vec3 color)
{
    Init();

    drawable = &renderer->CreateDrawable(vertices,
                                         indices,
                                         "shaders/color.vert.spv",
                                         "shaders/color.frag.spv",
                                         Renderer::LINES);

    glm::mat4& matrix = drawable->ubo.model;
    matrix = glm::translate(matrix, glm::vec3(glm::vec3(x, y, z)));
    matrix = glm::scale(matrix, scale);
}

void setRotation(const glm::vec3& rotation)
{
    //rotation = glm::vec3{0.1f, 0.1f, 0.1f};
};

void Cube::Update()
{
    //float tick = 0.0f;
    //tick += 0.01;
    //glm::vec3 mRotation = glm::vec3{0.5f, 0.5f, 0.0f};
}
