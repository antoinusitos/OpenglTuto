#ifndef DEF_GLTEXTURE
#define DEF_GLTEXTURE

#include "glew.h"

namespace OpenGLEngine
{

	using namespace std;

	struct GLTexture
	{
		GLuint id;
		int width;
		int height;
	};

}

#endif