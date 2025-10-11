#ifndef TEXTURE_H
#define TEXTURE_H

#include "Core/Utilities.h"

namespace gea
{

class Texture
{
public:
    Texture();

    std::string mTexturePath = PATH + "Assets/Textures/viking_room.png";
    uint32_t mMipLevels;
    VkImage mTextureImage;
    VkDeviceMemory mTextureImageMemory;
    VkImageView mTextureImageView;
    VkSampler mTextureSampler;
};

} //namespace gea

#endif // TEXTURE_H
