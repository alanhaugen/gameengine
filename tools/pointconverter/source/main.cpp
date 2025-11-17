#include <iostream>
#include <fstream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"

const int width = 512;
const int height = 512;
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
    long largestX = -999999;
    long largestY = -999999;
    long largestZ = -999999;
    long smallestX = 999999;
    long smallestY = 999999;
    long smallestZ = 999999;

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

        if (smallestX > pos.x)
        {
            smallestX = pos.x;
        }
        if (smallestY > pos.y)
        {
            smallestY = pos.y;
        }
        if (smallestZ > pos.z)
        {
            smallestZ = pos.z;
        }

        points.push_back(pos);
    }

    for (auto point : points)
    {
        float normX = (point.x - smallestX) / float(largestX - smallestX);
        float normZ = (point.z - smallestZ) / float(largestZ - smallestZ);
        float normY = (point.y - smallestY) / float(largestY - smallestY);

        int x = std::min(width  - 1, int(normX * (width  - 1)));
        int z = std::min(height - 1, int(normZ * (height - 1)));

        vertices[x][z] = u8(normY * 255.0f);
    }

    // Fill holes
    for (int z = 0; z < height; z++)
    {
        for (int x = 0; x < width; x++)
        {
            if (vertices[x][z] == 0)
            {
                int nearest = -1;

                // Look in a 3x3 neighborhood
                for (int dz = -1; dz <= 1; dz++)
                {
                    for (int dx = -1; dx <= 1; dx++)
                    {
                        int nx = x + dx;
                        int nz = z + dz;

                        if (nx >= 0 && nx < width && nz >= 0 && nz < height)
                        {
                            if (vertices[nx][nz] > 0)
                            {
                                nearest = vertices[nx][nz];
                            }
                        }
                    }
                }

                if (nearest >= 0)
                {
                    vertices[x][z] = nearest;
                }
            }
        }
    }

    // Generate image
    u8 *data;

    data = new u8[width * height * channels];

    int index = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //u8 scale = ((1.0f + stb_perlin_noise3(x * 0.01f,y * 0.01f,0.0f,0,0,0)) / 2.0f) * 256.0f;//vertices[x][y];
            u8 scale = vertices[x][y];

            data[index++] = scale;
        }
    }

    stbi_write_png("output.png", width, height, channels, data, width * channels);

    return 0;
}

