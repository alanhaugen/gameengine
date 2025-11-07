#ifndef MESH_H
#define MESH_H


// #define TINYOBJLOADER_IMPLEMENTATION
#include "External/tiny_obj_loader.h"

#include <QString>
#include "Core/Vertex.h"
#include <vulkan/vulkan_core.h>

namespace gea
{

class Mesh
{
public:
    Mesh();
    Mesh(QString MODEL_PATH);

    Mesh* loadModel(QString MODEL_PATH);
    std::vector<Vertex> mVertices;
    std::vector<uint32_t> mIndices;
    VkBuffer mVertexBuffer;
    VkBuffer mIndexBuffer;
    VkDeviceMemory mVertexBufferMemory;
    VkDeviceMemory mIndexBufferMemory;
    QString mPath;

    bool isUsed=false;

};

} // namespace gea

#endif // MESH_H
