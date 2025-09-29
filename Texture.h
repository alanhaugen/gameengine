#include "Utilities.h"
#ifndef TEXTURE_H
#define TEXTURE_H

namespace gea
{
    class Texture
    {
    public:
        Texture();

        std::string texturePath = PATH + "Assets/Textures/viking_room.png";
        uint32_t mipLevels;
        VkImage textureImage;
        VkDeviceMemory textureImageMemory;
        VkImageView textureImageView;
        VkSampler textureSampler;
    protected:
    };
}

#endif // TEXTURE_H