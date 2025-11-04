#ifndef TEXTURE_H
#define TEXTURE_H

#include "Core/Utilities.h"

namespace gea
{

class Texture
{
public:
    Texture();

    std::string mTexturePath;
    uint32_t mMipLevels;
    VkImage mTextureImage;
    VkDeviceMemory mTextureImageMemory;
    VkImageView mTextureImageView;
    VkSampler mTextureSampler;
    VkDescriptorSet textureDescriptor{};
};

} //namespace gea

#endif // TEXTURE_H
