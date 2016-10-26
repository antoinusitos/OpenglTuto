#include "ResourceManager.h"

TextureCache ResourceManager::textureCache;

GLTexture ResourceManager::GetTexture(string path)
{
	return textureCache.GetTexture(path);
}
