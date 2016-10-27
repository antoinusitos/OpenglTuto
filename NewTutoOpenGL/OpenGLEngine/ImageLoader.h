#ifndef DEF_IMAGELOADER
#define DEF_IMAGELOADER

#include "GLTexture.h"

#include <string>

namespace OpenGLEngine
{

	using namespace std;

	class ImageLoader
	{
	public:
		static GLTexture LoadPNG(string filePath);
	};

}

#endif