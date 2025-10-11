#ifndef MESH_H
#define MESH_H

#include "Utilities.h"

namespace gea
{
class Mesh
{
public:
    Mesh();
    void loadModel();

    std::string mModelPath = PATH + "Assets/Models/viking_room.obj";
    std::vector<Vertex> mVertices;
    std::vector<uint32_t> mIndices;
    VkBuffer mVertexBuffer;
    VkBuffer mIndexBuffer;
    VkDeviceMemory mVertexBufferMemory;
    VkDeviceMemory mIndexBufferMemory;
protected:
};

} // namespace gea

#endif // MESH_H
