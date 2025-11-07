#include "Mesh.h"
#include "External/tiny_obj_loader.h"
#include <qlogging.h>
#include <QMessageBox>
#include <stdexcept>
#include <unordered_map>

gea::Mesh::Mesh()
{
}

gea::Mesh::Mesh(QString MODEL_PATH)
{
	mVertexBuffer = VK_NULL_HANDLE;
	mIndexBuffer = VK_NULL_HANDLE;
	mVertexBufferMemory = VK_NULL_HANDLE;
	mIndexBufferMemory = VK_NULL_HANDLE;
    mPath=MODEL_PATH;
    loadModel(MODEL_PATH);
}

gea::Mesh* gea::Mesh::loadModel(QString MODEL_PATH)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.toStdString().c_str())) 
    {
        QString msg = "Could not load model " + MODEL_PATH;
        QMessageBox::critical(nullptr, "Error", msg);
        throw std::runtime_error(warn + err);
    }

    std::unordered_map<Vertex, uint32_t> uniqueVertices{};
    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
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

            vertex.color = {1.0f, 1.0f, 1.0f};


            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(mVertices.size());
                mVertices.push_back(vertex);
            }

            mIndices.push_back(uniqueVertices[vertex]);
        }
    }
    return this;
}
