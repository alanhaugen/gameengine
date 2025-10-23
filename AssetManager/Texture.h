#ifndef TEXTURE_H
#define TEXTURE_H

// #define STB_IMAGE_IMPLEMENTATION
// #include "External/stb_image.h"

#include "Core/Utilities.h"
#include <QString>
#include <stdexcept>

namespace gea
{

class Texture
{
public:
    Texture();

   //should be commented out
    std::string mTexturePath = PATH + "Assets/Textures/viking_room.png";

    int texWidth, texHeight, texChannels;
    uint32_t mMipLevels;
    VkImage mTextureImage;
    VkDeviceMemory mTextureImageMemory;
    VkImageView mTextureImageView;
    VkSampler mTextureSampler;
    bool isUsed=false;
    void createTextureImage(QString MODEL_PATH);
};

} //namespace gea

#endif // TEXTURE_H
