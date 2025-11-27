#include "mesh.h"
#include <qdebug.h>
#include "gameobject.h"
#include "glm/gtc/matrix_transform.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_NO_STB_IMAGE_WRITE
#include "tiny_gltf.h"

#include <unordered_map>

Mesh::Mesh(const char *filePath,
           const char* vertexShaderPath,
           const char* fragmentShaderPath)
{
    name = "Mesh";

    if (GetFileExtension(filePath) == "obj")
    {
        loadMesh(filePath, vertexShaderPath, fragmentShaderPath);
    }
    if (GetFileExtension(filePath) == "glb")
    {
        loadMeshGLTF(filePath, vertexShaderPath, fragmentShaderPath);
    }
}

void Mesh::loadMesh(const char *filePath, const char *vertexShaderPath, const char *fragmentShaderPath)
{
    //imcomplete
    if(drawable)
    {
        Hide();
    }

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

    if(texture.empty())
    {
        if (materials.size() > 0)
        {
            texture = materials[0].diffuse_texname.c_str();
        }
        else
        {
            //texture = "Assets/Textures/pink.jpg";
        }
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

            vertex.color = {0.0f, 0.0f, 0.0f};

            if (attrib.normals.empty() == false)
            {
                vertex.normal = {
                     attrib.normals[3 * index.normal_index + 0],
                     attrib.normals[3 * index.normal_index + 1],
                     attrib.normals[3 * index.normal_index + 2]
                };
            }

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                vertices.push_back(vertex);
            }

            indices.push_back(uniqueVertices[vertex]);
        }
    }

    drawable = &renderer->CreateDrawable(vertices, indices, vertexShaderPath, fragmentShaderPath, Renderer::TRIANGLES, texture.c_str());
}

void Mesh::loadMeshGLTF(const char *filePath, const char *vertexShaderPath, const char *fragmentShaderPath)
{
    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;

    bool res = loader.LoadBinaryFromFile(&model, &err, &warn, filePath);

    if (!err.empty())
    {
        LogWarning(err);
    }

    if (!warn.empty())
    {
        LogWarning(warn);
    }

    if (res == false)
    {
        LogError("Failed to load mesh");
        exit(0);
    }

    const tinygltf::Scene &scene = model.scenes[model.defaultScene];

    for (size_t i = 0; i < scene.nodes.size(); ++i)
    {
        tinygltf::Node node = model.nodes[scene.nodes[i]];

        if ((node.mesh >= 0) && (node.mesh < model.meshes.size()))
        {
            //bindMesh(vbos, model, model.meshes[node.mesh]);
        }
    }
}

void Mesh::Update()
{
    if (gameObject)
    {
        drawable->ubo.model = gameObject->matrix;
    }
}

std::string Mesh::GetFileExtension(const char *string)
{
    std::string stdString = std::string(string);

    return stdString.substr(stdString.length() - 3);
}
