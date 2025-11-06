#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

const int width = 256;
const int height = 256;
const int channels = 1;

typedef uint8_t u8;

int main()
{
    u8 *data;

    data = new u8[width * height * channels];

    int index = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            u8 scale = 255;

            data[++index] = scale;
        }
    }

    stbi_write_png("output.png", width, height, channels, data, width * channels);

    return 0;
}

