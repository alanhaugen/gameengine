#include "sphere.h"
#include "core/components/gameobject.h"

void Sphere::GenerateIcoSphere(const char *vert, const char *frag, const char* texture)
{
    // Generate a sphere (TODO: implement for fun)
    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;

    drawable = renderer->CreateDrawable(vertices, indices, vert, frag);
}

void Sphere::GenerateUVSphere(const char *vert, const char *frag, const char* texture)
{
    // Thanks to https://www.songho.ca/opengl/gl_sphere.html
    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;

    float radius = 1.0f;
    const int stackCount = 32;
    const int sectorCount = 32;

    float pi = glm::pi<float>();
    float stackStep  = pi / stackCount;
    float sectorStep = 2.0f * pi / sectorCount;

    // Generate vertices
    for (int i = 0; i <= stackCount; ++i)
    {
        float stackAngle = pi / 2.0f - i * stackStep;   // +pi/2 to -pi/2
        float xy = radius * cosf(stackAngle);
        float z  = radius * sinf(stackAngle);

        for (int j = 0; j <= sectorCount; ++j)
        {
            float sectorAngle = j * sectorStep; // 0 to 2pi

            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);

            Vertex vertex;
            vertex.pos = glm::vec3(x, y, z);

            // Normal = normalized position for a sphere
            vertex.normal = glm::normalize(vertex.pos);

            // UV coordinates (0-1)
            vertex.texCoord = glm::vec2(
                (float)j / sectorCount,
                (float)i / stackCount
                );

            vertices.push_back(vertex);
        }
    }

    // Generate index buffer
    for (int i = 0; i < stackCount; ++i)
    {
        int k1 = i * (sectorCount + 1);
        int k2 = k1 + sectorCount + 1;

        for (int j = 0; j < sectorCount; ++j)
        {
            // Ignore top and bottom poles
            if (i != 0)
            {
                indices.push_back(k1 + j);
                indices.push_back(k2 + j);
                indices.push_back(k1 + j + 1);
            }

            if (i != (stackCount - 1))
            {
                indices.push_back(k1 + j + 1);
                indices.push_back(k2 + j);
                indices.push_back(k2 + j + 1);
            }
        }
    }

    drawable = renderer->CreateDrawable(vertices, indices, vert, frag, Renderer::TRIANGLES, texture, true, isInstanced);
}

void Sphere::Init(const char *vert, const char *frag, const char *texture)
{
    name = "Sphere";

    GenerateUVSphere(vert, frag, texture);
}

Sphere::Sphere(const char* texture)
{
    if (texture[0] == '\0')
    {
        Init("shaders/color.vert.spv", "shaders/color.frag.spv", texture);
    }
    else
    {
        Init("shaders/phong.vert.spv", "shaders/phong.frag.spv", texture);
    }

    if (texture[0] == '\0')
    {
        renderer->SetColour(drawable, glm::vec4(1.0f));
    }
}

Sphere::Sphere(float x, float y, float z, glm::vec3 scale)
{
    Init();

    renderer->Translate(drawable, glm::vec3(x, y, z));
    renderer->Scale(drawable, scale);
}

Sphere::Sphere(glm::vec3 scale, glm::vec3 colour, const char* vertShader, const char* fragShader, bool instanced)
{
    isInstanced = instanced;
    Init(vertShader, fragShader);

    renderer->Scale(drawable, scale);
    renderer->SetColour(drawable, glm::vec4(colour, 1.0f));
}

void Sphere::Update(float deltaTime)
{
    if (gameObject)
    {
        renderer->SetModel(drawable, gameObject->matrix);
    }
}
