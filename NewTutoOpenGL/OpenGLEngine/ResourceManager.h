#ifndef DEF_RESOURCEMANAGER
#define DEF_RESOURCEMANAGER

#include "TextureCache.h"
#include <string.h>

using namespace std;

class ResourceManager
{
public:
	static GLTexture GetTexture(string path);

private:
	static TextureCache textureCache;
};

#endif