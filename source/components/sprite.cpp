#include "sprite.h"

Sprite::Sprite(float x, float y, const char *glyphs)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    Vertex bottomLeft(-1, -1, 0); // 0
    Vertex bottomRight(1, -1, 0); // 1
    Vertex topRight(1, 1, 0);     // 2
    Vertex topLeft(-1, 1, 0);     // 3

    bottomLeft.texCoord  = glm::vec2(0, 1);
    bottomRight.texCoord = glm::vec2(1, 1);
    topRight.texCoord    = glm::vec2(1, 0);
    topLeft.texCoord     = glm::vec2(0, 0);

    vertices.push_back(bottomLeft);
    vertices.push_back(bottomRight);
    vertices.push_back(topRight);
    vertices.push_back(topLeft);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);

    drawable = &renderer->CreateDrawable(vertices,
                                         indices,
                                         "shaders/shader.vert.spv",
                                         "shaders/shader.frag.spv",
                                         Renderer::TRIANGLES,
                                         "Assets/Textures/orange.jpg");
}

void Sprite::Update()
{
}
