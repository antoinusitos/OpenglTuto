#ifndef DEF_IMAGELOADER
#define DEF_IMAGELOADER

#include "UserIncludes.h"
#include "GLTexture.h"

class ImageLoader
{
public:
	GLTexture LoadPNG(string filePath);
};

#endif