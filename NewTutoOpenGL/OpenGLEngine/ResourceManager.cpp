#include "ResourceManager.h"

namespace OpenGLEngine
{

	TextureCache ResourceManager::textureCache;

	GLTexture ResourceManager::GetTexture(string path)
	{
		return textureCache.GetTexture(path);
	}

}