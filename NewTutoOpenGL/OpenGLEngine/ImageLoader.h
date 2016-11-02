#ifndef DEF_IMAGELOADER
#define DEF_IMAGELOADER

#include "GLTexture.h"

#include <string>

namespace OpenGLEngine
{

	class ImageLoader
	{
	public:
		static GLTexture LoadPNG(std::string filePath);
	};

}

#endif