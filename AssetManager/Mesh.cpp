#include "Mesh.h"
#include "External/tiny_obj_loader.h"
#include <qlogging.h>
#include <QMessageBox>
#include <stdexcept>

gea::Mesh::Mesh()
{
	mVertexBuffer = VK_NULL_HANDLE;
	mIndexBuffer = VK_NULL_HANDLE;
	mVertexBufferMemory = VK_NULL_HANDLE;
	mIndexBufferMemory = VK_NULL_HANDLE;
    loadModel();
}

void gea::Mesh::loadModel()
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, mModelPath.c_str()))
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Could not load model!");
        messageBox.setFixedSize(500,200);
        throw std::runtime_error(warn + err);
    }


    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    for (const auto& shape : shapes)
    {
        for (const auto& index : shape.mesh.indices)
        {
            Vertex vertex{};

            vertex.pos = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.texCoord = {
                attrib.texcoords[2 * index.texcoord_index + 0],
                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.color = { 1.0f, 1.0f, 1.0f };

            if (uniqueVertices.count(vertex) == 0)
            {
                uniqueVertices[vertex] = static_cast<uint32_t>(mVertices.size());
                mVertices.push_back(vertex);
            }

            mIndices.push_back(uniqueVertices[vertex]);
        }
    }
}
