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

        std::string modelPath = PATH + "Assets/Models/viking_room.obj";
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        VkBuffer vertexBuffer;
        VkBuffer indexBuffer;
        VkDeviceMemory vertexBufferMemory;
        VkDeviceMemory indexBufferMemory;
    protected:
    };

}   // namespace gea

#endif // MESH_H
