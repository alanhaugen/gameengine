#include "mesh.h"
#include <qdebug.h>
#include "gameobject.h"
#include "glm/gtc/matrix_transform.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <unordered_map>

Mesh::Mesh(const char *filePath,
           const char* vertexShaderPath,
           const char* fragmentShaderPath)
{
    SetName("Mesh");
    FilePath =filePath;
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath, "Assets/Models")) {
        LogError(warn+err+"\nTry downloading the assets files or changing the working directory");
        exit(0);
    }

    const char* texture = "";

    if (materials.size() > 0)
    {
        texture = materials[0].diffuse_texname.c_str();
    }

    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex;

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

            // vertex.normal = {
            //     attrib.normals[3 * index.vertex_index + 0],
            //     attrib.normals[3 * index.vertex_index + 1],
            //     attrib.normals[3 * index.vertex_index + 2]
            // };

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                vertices.push_back(vertex);
            }

            indices.push_back(uniqueVertices[vertex]);
        }
    }

    drawable = &renderer->CreateDrawable(vertices, indices, vertexShaderPath, fragmentShaderPath, Renderer::TRIANGLES, texture);
}

void Mesh::Update()
{

    if(!entityOwner || !drawable)
    {
        return;
    }


    //qDebug()<<"Meshpos: "<<mTransform.mPosition.x;

}

void Mesh::OnAttach()
{
    //attached the drawable to the gameobject so gameObject is able to control the transform
    // if(gameobjOwner)
    // {
    //     gameobjOwner->drawable = drawable;
    // }
}

void Mesh::UpdateTransform(Transform transform)
{

    mTransform = transform;
    //multiplies the value by 1 instead of zero
    glm::mat4 Neutral = glm::mat4(1.0f);


    //Position
    Neutral = glm::translate(Neutral,mTransform.mPosition);
    //rotation
    Neutral  = glm::rotate(Neutral, glm::radians(mTransform.mRotation.x),  glm::vec3(1,0,0));
    Neutral  = glm::rotate(Neutral, glm::radians(mTransform.mRotation.y),  glm::vec3(0,1,0));
    Neutral = glm::rotate(Neutral, glm::radians(mTransform.mRotation.z),  glm::vec3(0,0,1));
    //scale
    Neutral = glm::scale(Neutral,mTransform.mScale);

    drawable->ubo.model = Neutral;

    // qDebug() << "Mesh Transform updated:"
    //          << "Pos" << mTransform.mPosition.x << mTransform.mPosition.y << mTransform.mPosition.z
    //          << "Rot" << mTransform.mRotation.x << mTransform.mRotation.y << mTransform.mRotation.z
    //          << "Scale" << mTransform.mScale.x << mTransform.mScale.y << mTransform.mScale.z;

}
