#include "terrain.h"

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
           const char* vertexShaderPath,
           const char* fragmentShaderPath)
{
    Init(); // todo: change into reading data from file

    drawable = &renderer->CreateDrawable(vertices, indices, vertexShaderPath, fragmentShaderPath);
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

/*
#include "HeightMap.h"
#include "Vertex.h"
#include "stb_image.h"

HeightMap::HeightMap()
{ }

void HeightMap::makeTerrain(std::string heightMapImage)
{
    //Load the heightmap image
    //Using stb_image to load the image
    stbi_uc* pixelData = stbi_load(heightMapImage.c_str(), &mWidth, &mHeight, &mChannels, STBI_rgb_alpha);
    if (pixelData == nullptr)
    {
        qDebug() << "Failed to load heightmap image!";
        return;
    }
    //Make the terrain from the pixel data
    makeTerrain(pixelData, mWidth, mHeight);
    stbi_image_free(pixelData);

}

//Function that makes a terrain grid from a heightmap, using the values in the heightmap as height.
//This function will crash if the width and height of the heightmap is not set correct!
//The size of the textureData array is widthIn * heightIn.
// The function is not tested in this codebase, and is provided as an example.
void HeightMap::makeTerrain(unsigned char* textureData, int widthIn, int heightIn)
{
    //Default normal pointing straight up - should be calculated correctly for lights to work!!!
    float normal[3]{0.f, 1.f, 0.f};

    //How many meters between each vertex in both x and z direction
    //This should be sent in as a parameter!
    float horisontalSpacing{.2f};

    //Scaling the height read from the heightmap. 0 -> 255 meters if this is set to 1
    //This should be sent in as a parameter!
    float heightSpacing{.02f};

    //Offset the whole terrain in y (height) axis
    //Moves the terrain mesh up or down
    //Because of Barycentric calculations, we want the terrain to be in World coordinates!
    //So we don't want to move the terrain up or down in the Y axis after it is made
    float heightPlacement{-10.f};

    //Getting the scale of the heightmap
    //Using depth as the name of texture height, to not confuse with terrain height
    unsigned short width = widthIn;       //Width == x-axis
    unsigned short depth = heightIn;      //Depth == z-axis

    //Temp variables for creating the mesh
    //Adding offset so the middle of the terrain will be in World origo
    float vertexXStart{ 0.f - width * horisontalSpacing / 2 };            // if world origo should be at center use: {0.f - width * horisontalSpacing / 2};
    float vertexZStart{ 0.f + depth * horisontalSpacing / 2 };            // if world origo should be at center use: {0.f + depth * horisontalSpacing / 2};

    //Loop to make the mesh from the values read from the heightmap (textureData)
    //Double for-loop to make the depth and the width of the terrain in one go
    for(int d{0}; d < depth; ++d)       //depth loop
    {
        for(int w{0}; w < width; ++w)   //width loop
        {
            //Heightmap image is actually stored as an one dimentional array - so calculating the correct index for column and row
            //and scale it according to variables
            // Calculate the correct index for the R value of each pixel
            int index = (w + d * width) * 4; // Each pixel has 4 bytes (RGBA)
            float heightFromBitmap = static_cast<float>(textureData[index]) * heightSpacing + heightPlacement;
            //                                          x - value                      y-value               z-value
            mVertices.emplace_back(Vertex{vertexXStart + (w * horisontalSpacing), heightFromBitmap, vertexZStart - (d * horisontalSpacing),
                //  dummy normal=0,1,0                  Texture coordinates
                normal[0],normal[1],normal[2],           w / (width - 1.f), d / (depth - 1.f)});
        }
    }

    // The mesh(grid) is drawn in quads with diagonals from lower left to upper right
    //          _ _
    //         |/|/|
    //          - -
    //         |/|/|
    //          - -
    //Making the indices for this mesh:
    for(int d{0}; d < depth-1; ++d)        //depth - 1 because we draw the last quad from depth - 1 and in negative z direction
    {
        for(int w{0}; w < width-1; ++w)    //width - 1 because we draw the last quad from width - 1 and in positive x direction
        {
            //Indices for one quad:
            mIndices.emplace_back(w + d * width);               // 0 + 0 * mWidth               = 0
            mIndices.emplace_back(w + d * width + width + 1);   // 0 + 0 * mWidth + mWidth + 1  = mWidth + 1
            mIndices.emplace_back(w + d * width + width);       // 0 + 0 * mWidth + mWidth      = mWidth
            mIndices.emplace_back(w + d * width);               // 0 + 0 * mWidth               = 0
            mIndices.emplace_back(w + d * width + 1);           // 0 + 0 * mWidth + 1           = 1
            mIndices.emplace_back(w + d * width + width + 1);   // 0 + 0 * mWidth + mWidth + 1  = mWidth + 1
        }
    }


    //Calculating the normals for the mesh
    //Function not made yet:
    //calculateHeighMapNormals();
}

*/
