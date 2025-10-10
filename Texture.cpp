#include "Texture.h"

gea::Texture::Texture()
{
	mipLevels = 1;
	textureImage = VK_NULL_HANDLE;
	textureImageMemory = VK_NULL_HANDLE;
	textureImageView = VK_NULL_HANDLE;
	textureSampler = VK_NULL_HANDLE;
}