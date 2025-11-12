#ifndef TEXTURE_H
#define TEXTURE_H

// #define STB_IMAGE_IMPLEMENTATION
#include "External/stb_image.h"
#include <vulkan/vulkan_core.h>

#include <QString>
#include <stdexcept>

namespace gea
{

class Texture
{
public:
    //Texture();
    Texture(QString MODEL_PATH);

    QString mPath;

    int mTexWidth{0}, mTexHeight{0}, mTexChannels{0};
    uint32_t mMipLevels;
    VkImage mTextureImage;
    VkDeviceMemory mTextureImageMemory;
    VkImageView mTextureImageView;
    VkSampler mTextureSampler;

    VkDescriptorSet textureDescriptor;
    VkDescriptorSetLayout textureDescriptorSetLayout;

    stbi_uc* mPixels{ nullptr };
    bool isUsed{ false };
    void createTextureImage(QString MODEL_PATH);
};

} //namespace gea

#endif // TEXTURE_H
