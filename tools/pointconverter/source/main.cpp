#include <iostream>
#include <fstream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"

const int width = 256;
const int height = 256;
const int channels = 1;

typedef uint8_t u8;

struct vec3
{
    float x,y,z;

    vec3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    vec3(float inx, float iny, float inz)
    {
        x = inx;
        y = iny;
        z = inz;
    }

    vec3 operator+(vec3 other)
    {
        vec3 result;
        result.x = x + other.x;
        result.y = y + other.y;
        result.z = z + other.z;

        return result;
    }

    vec3 operator-(vec3 other)
    {
        vec3 result;
        result.x = x - other.x;
        result.y = y - other.y;
        result.z = z - other.z;

        return result;
    }
};

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::cout << "Usage: pointconverter <filename>" << std::endl;
        return -1;
    }

    std::ifstream infile(argv[1]);

    int vertices[width][height];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < width; j++)
        {
            vertices[i][j] = 0;
        }
    }

    std::vector<vec3> points;
    float largestX = -100000;
    float largestY = -100000;
    float largestZ = -100000;

    float x, y, z;
    while (infile >> x >> z >> y) // Notice z and y are swapped
    {
        static vec3 offset = vec3(x, y, z);

        vec3 pos = vec3(x, y, z) - offset;

        if (largestX < pos.x)
        {
             largestX = pos.x;
        }
        if (largestY < pos.y)
        {
             largestY = pos.y;
        }
        if (largestZ < pos.z)
        {
             largestZ = pos.z;
        }

        points.push_back(pos);
    }

    for (auto point : points)
    {
        int x = abs((point.x / largestX) * 255);
        int y = abs((point.y / largestY) * 255);
        int z = abs((point.z / largestZ) * 255);

        vertices[x][z] = y;
    }

    u8 *data;

    data = new u8[width * height * channels];

    int index = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //u8 scale = ((1.0f + stb_perlin_noise3(x * 0.01f,y * 0.01f,0.0f,0,0,0)) / 2.0f) * 256.0f;//vertices[x][y];
            u8 scale = vertices[x][y];

            data[++index] = scale;
        }
    }

    stbi_write_png("output.png", width, height, channels, data, width * channels);

    return 0;
}

