#include "TextureCache.h"
#include "ImageLoader.h"

TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

GLTexture TextureCache::GetTexture(string path)
{
	// lookup the texture and see if it's in the map
	auto mit = textureMap.find(path);
	

	// check if it's not in the map
	if (mit == textureMap.end())
	{
		// load the texture
		GLTexture newTexture = ImageLoader::LoadPNG(path);
		
		// insert it into the map
		textureMap.insert(make_pair(path, newTexture));

		return newTexture;
	}

	return mit->second;
}
