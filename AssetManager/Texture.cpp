#include "Texture.h"

// gea::Texture::Texture() //(model_path)
// {
// 	mMipLevels = 1;
// 	mTextureImage = VK_NULL_HANDLE;
// 	mTextureImageMemory = VK_NULL_HANDLE;
// 	mTextureImageView = VK_NULL_HANDLE;
// 	mTextureSampler = VK_NULL_HANDLE;
// }

gea::Texture::Texture(QString MODEL_PATH)
{
    mMipLevels = 1;
    mTextureImage = VK_NULL_HANDLE;
    mTextureImageMemory = VK_NULL_HANDLE;
    mTextureImageView = VK_NULL_HANDLE;
    mTextureSampler = VK_NULL_HANDLE;
    mPath=MODEL_PATH;
    createTextureImage(MODEL_PATH);

}

void gea::Texture::createTextureImage(QString MODEL_PATH)
{

        mPixels = stbi_load(MODEL_PATH.toStdString().c_str(), &mTexWidth, &mTexHeight, &mTexChannels, STBI_rgb_alpha);
        //VkDeviceSize imageSize = mTexWidth * mTexHeight * 4; //in Renderer
        mMipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(mTexWidth, mTexHeight)))) + 1;

        if (!mPixels) {
            throw std::runtime_error("failed to load texture image!");
        }
}
