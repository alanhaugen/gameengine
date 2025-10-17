#include "sprite.h"

Sprite::Sprite()
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    vertices.push_back(Vertex(-1, -1, 0)); // 0  bottom left
    vertices.push_back(Vertex(1, -1, 0));  // 1  bottom right
    vertices.push_back(Vertex(1, 1, 0));   // 2  top right
    vertices.push_back(Vertex(-1, 1, 0));  // 3  top left - B

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    indices.push_back(1);
    indices.push_back(3);
    indices.push_back(2);

    drawable = &renderer->CreateDrawable(vertices,
                                        indices,
                                        "shaders/color.vert.spv",
                                        "shaders/color.frag.spv");
}

void Sprite::Update()
{
}
