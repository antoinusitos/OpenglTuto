#ifndef DEF_TEXTURECACHE
#define DEF_TEXTURECACHE

#include <map>
#include "GLTexture.h"

namespace OpenGLEngine
{

	using namespace std;

	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture GetTexture(string path);

	private:
		map<string, GLTexture> textureMap;
	};

}

#endif