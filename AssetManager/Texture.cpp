#include "Texture.h"

gea::Texture::Texture()
{
	mMipLevels = 1;
	mTextureImage = VK_NULL_HANDLE;
	mTextureImageMemory = VK_NULL_HANDLE;
	mTextureImageView = VK_NULL_HANDLE;
	mTextureSampler = VK_NULL_HANDLE;
}