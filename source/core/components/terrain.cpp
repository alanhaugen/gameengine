#include "terrain.h"
#include "stb_image.h"

void Terrain::Init()
{
    vertices.push_back(Vertex(0, 0, 0, glm::vec3(1,0.5,0))); // 0  bottom left
    vertices.push_back(Vertex(0, -0.2,  1, glm::vec3(0.5,1,0))); // 1  bottom left
    vertices.push_back(Vertex(1, -0.5, 0, glm::vec3(0,0.5,1))); // 2  top right
    vertices.push_back(Vertex(1, -0.4,  1, glm::vec3(0.7,0,0))); // 3  top left - B

    vertices.push_back(Vertex(2, 0.3,  1, glm::vec3(1,0,0))); // 4 bottom right
    vertices.push_back(Vertex(2, 0.8,  0, glm::vec3(0,1,0)));  //5 C

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    indices.push_back(1);
    indices.push_back(3);
    indices.push_back(2);

    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(4);

    indices.push_back(2);
    indices.push_back(4);
    indices.push_back(5);
}

Terrain::Terrain()
{
    Init();

    drawable = &renderer->CreateDrawable(vertices, indices, "shaders/color.vert.spv", "shaders/color.frag.spv");
}

Terrain::Terrain(const char *filePath,
                 const char* texturePath,
                 const char* vertexShaderPath,
                 const char* fragmentShaderPath,
                 bool isCloud)
{
    int width,height,n;
    unsigned char *data = stbi_load(filePath, &width, &height, &n, 0);

    if (n != 1)
    {
        LogError("The texture used for the terrain has to many colour channles. Only images with one 8-bit grayscale channel are supported");
        exit(0);
    }

    int index = 0;
    for (int y = 0; y < height - 1; y++)
    {
        for (int x = 0; x < width - 1; x++)
        {
            glm::vec3 topLeft     = glm::vec3(x, data[x + y * width], y);
            glm::vec3 topRight    = glm::vec3(x + 1, data[(x + 1) + y * width], y);
            glm::vec3 bottomLeft  = glm::vec3(x, data[x + (y + 1) * width], y + 1);
            glm::vec3 bottomRight = glm::vec3(x + 1, data[(x + 1) + (y + 1) * width], y + 1);

            glm::vec2 uvTopLeft(x / float(width), y / float(height));
            glm::vec2 uvTopRight((x + 1) / float(width), y / float(height));
            glm::vec2 uvBottomLeft(x / float(width), (y + 1) / float(height));
            glm::vec2 uvBottomRight((x + 1) / float(width), (y + 1) / float(height));

            Vertex v1 = Vertex(bottomLeft, uvBottomLeft);
            Vertex v2 = Vertex(bottomRight, uvBottomRight);
            Vertex v3 = Vertex(topRight, uvTopRight);
            Vertex v4 = Vertex(topLeft, uvBottomLeft);

            vertices.push_back(v1);
            vertices.push_back(v2);
            vertices.push_back(v3);
            vertices.push_back(v4);

            indices.push_back(0 + index);
            indices.push_back(1 + index);
            indices.push_back(2 + index);

            indices.push_back(2 + index);
            indices.push_back(3 + index);
            indices.push_back(0 + index);

            index += 4;
        }
    }

    if (isCloud)
    {
        drawable = &renderer->CreateDrawable(vertices, indices, vertexShaderPath, fragmentShaderPath, Renderer::POINTS, texturePath);
    }
    else
    {
        drawable = &renderer->CreateDrawable(vertices, indices, vertexShaderPath, fragmentShaderPath, Renderer::TRIANGLES, texturePath);
    }
}

void Terrain::Update()
{
}

float Terrain::GetHeightAt(float x, float z) const
{
    return GetHeightAt(glm::vec3(x, 0, z));
}

float Terrain::GetHeightAt(const glm::vec3 positionXZ) const
{
    glm::vec2 point(positionXZ.x, positionXZ.z);

    for (size_t i = 0; i < indices.size(); i += 3) {
        const Vertex& v0 = vertices[indices[i]];
        const Vertex& v1 = vertices[indices[i + 1]];
        const Vertex& v2 = vertices[indices[i + 2]];

        glm::vec2 a(v0.pos.x, v0.pos.z);
        glm::vec2 b(v1.pos.x, v1.pos.z);
        glm::vec2 c(v2.pos.x, v2.pos.z);

        glm::vec2 v0v2 = c - a;
        glm::vec2 v0v1 = b - a;
        glm::vec2 v0p = point - a;

        float d00 = glm::dot(v0v1, v0v1);
        float d01 = glm::dot(v0v1, v0v2);
        float d11 = glm::dot(v0v2, v0v2);
        float d20 = glm::dot(v0p, v0v1);
        float d21 = glm::dot(v0p, v0v2);

        float denom = d00 * d11 - d01 * d01;
        if (denom == 0.0f) continue;

        float v = (d11 * d20 - d01 * d21) / denom;
        float w = (d00 * d21 - d01 * d20) / denom;
        float u = 1.0f - v - w;

        if (u >= 0.0f && v >= 0.0f && w >= 0.0f) {
            return v0.pos.y * u + v1.pos.y * v + v2.pos.y * w;
        }
    }

    return 0.0f;  // Default flat
}

glm::vec3 Terrain::GetNormal(const glm::vec3 position) const
{
    glm::vec2 point(position.x, position.z);

    for (size_t i = 0; i < indices.size(); i += 3) {
        const Vertex& v0 = vertices[indices[i]];
        const Vertex& v1 = vertices[indices[i + 1]];
        const Vertex& v2 = vertices[indices[i + 2]];

        glm::vec2 a(v0.pos.x, v0.pos.z);
        glm::vec2 b(v1.pos.x, v1.pos.z);
        glm::vec2 c(v2.pos.x, v2.pos.z);

        glm::vec2 v0v2 = c - a;
        glm::vec2 v0v1 = b - a;
        glm::vec2 v0p = point - a;

        float d00 = glm::dot(v0v1, v0v1);
        float d01 = glm::dot(v0v1, v0v2);
        float d11 = glm::dot(v0v2, v0v2);
        float d20 = glm::dot(v0p, v0v1);
        float d21 = glm::dot(v0p, v0v2);

        float denom = d00 * d11 - d01 * d01;
        if (denom == 0.0f) continue;

        float v = (d11 * d20 - d01 * d21) / denom;
        float w = (d00 * d21 - d01 * d20) / denom;
        float u = 1.0f - v - w;

        if (u >= 0.0f && v >= 0.0f && w >= 0.0f)
        {
            glm::vec3 dir;
            glm::vec3 p1(v0.pos.x, v0.pos.y, v0.pos.z);
            glm::vec3 p2(v1.pos.x, v1.pos.y, v1.pos.z);
            glm::vec3 p3(v2.pos.x, v2.pos.y, v2.pos.z);

            glm::vec3 A = p2 - p1;
            glm::vec3 B = p3 - p1;

            dir.x = A.y * B.z - A.z * B.y;
            dir.y = A.z * B.x - A.x * B.z;
            dir.z = A.x * B.y - A.y * B.x;

            return dir;
        }
    }
    return glm::vec3();
}
