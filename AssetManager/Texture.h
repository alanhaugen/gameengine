#ifndef TEXTURE_H
#define TEXTURE_H

// #define STB_IMAGE_IMPLEMENTATION
#include "External/stb_image.h"

#include "Core/Utilities.h"
#include <QString>
#include <stdexcept>

namespace gea
{

class Texture
{
public:
    //Texture();
    Texture(QString MODEL_PATH);

   //should be commented out
    std::string mTexturePath = PATH + "Assets/Textures/viking_room.png";

    int mTexWidth{0}, mTexHeight{0}, mTexChannels{0};
    uint32_t mMipLevels;
    VkImage mTextureImage;
    VkDeviceMemory mTextureImageMemory;
    VkImageView mTextureImageView;
    VkSampler mTextureSampler;
    stbi_uc* mPixels;
    bool isUsed=false;
    void createTextureImage(QString MODEL_PATH);

};

} //namespace gea

#endif // TEXTURE_H
