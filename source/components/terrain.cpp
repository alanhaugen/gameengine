#include "terrain.h"

Terrain::Terrain(const char *filePath,
           const char* vertexShaderPath,
           const char* fragmentShaderPath)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    vertices.push_back(Vertex(-10, -2, -10)); // 0  bottom left
    vertices.push_back(Vertex( 10, -2,  10)); // 1  top right
    vertices.push_back(Vertex( 10, -2, -10)); // 2  bottom right
    vertices.push_back(Vertex(-10, -2,  10)); // 3  top left

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(0);
    indices.push_back(3);
    indices.push_back(1);

    drawable = &renderer->CreateDrawable(vertices, indices, vertexShaderPath, fragmentShaderPath);
}

void Terrain::Update()
{

}
