#ifndef MESH_H
#define MESH_H

#include "Core/Utilities.h"
#include <QString>
#include "Core/Vertex.h"
namespace gea
{
class Mesh
{
public:
    Mesh();
    Mesh(QString MODEL_PATH);
    void loadModel();
    QString mModelPath = QString::fromStdString(PATH + "Assets/Models/viking_room.obj");
    std::string mModelPath_find_bug = PATH + "Assets/Models/viking_room.obj";

    Mesh* loadModel(QString MODEL_PATH);
    std::vector<Vertex> mVertices;
    std::vector<uint32_t> mIndices;
    VkBuffer mVertexBuffer;
    VkBuffer mIndexBuffer;
    VkDeviceMemory mVertexBufferMemory;
    VkDeviceMemory mIndexBufferMemory;
    QString mPath;
    bool isUsed=false;
    bool isMesh=true;
protected:
};

} // namespace gea

#endif // MESH_H
