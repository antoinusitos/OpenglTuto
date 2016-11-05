#include "Window.h"
#include "Errors.h"

namespace OpenGLEngine
{

	Window::Window() : sdlWindow(nullptr)
	{
	}

	Window::~Window()
	{
	}

	int Window::Create(string theWindowName, int theScreenWidht, int theScreenHeight, unsigned int currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		// create the window
		sdlWindow = SDL_CreateWindow(theWindowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, theScreenWidht, theScreenHeight, flags);

		if (sdlWindow == nullptr)
		{
			FatalError("SDL Window could not be created!");
		}

		// create a context for the window
		SDL_GLContext glContext = SDL_GL_CreateContext(sdlWindow);
		if (glContext == nullptr)
		{
			FatalError("SDL_GL Context could not be created!");
		}

		// init glew
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			FatalError("could not be initialize glew!");
		}

		// check the OpenGL Version
		printf("***   OpenGL Version : %s   ***\n", glGetString(GL_VERSION));

		// put a blue clear screen
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		// set vsync off
		SDL_GL_SetSwapInterval(0);

		// enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::SwapBuffer()
	{
		// swap the buffer and draw everything
		SDL_GL_SwapWindow(sdlWindow);
	}

}