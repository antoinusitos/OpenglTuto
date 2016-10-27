#include <SDL.h>
#include <glew.h>

#include "OpenGLEngine.h"

namespace OpenGLEngine
{

	int Init()
	{
		// Initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		// init sdl
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}

}