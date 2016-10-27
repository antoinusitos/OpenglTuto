#ifndef DEF_WINDOW
#define DEF_WINDOW

#include "SDL.h"
#include "glew.h"

#include <string>

namespace OpenGLEngine
{

	using namespace std;

	enum WindowFlags
	{
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4,
	};

	class Window
	{
	public:
		Window();
		~Window();

		int Create(string theWindowName, int theScreenWidht, int theScreenHeight, unsigned int currentFlags);

		void SwapBuffer();

		int GetScreenWidth() { return screenWidth; }
		int GetScreenHeight() { return screenHeight; }

	private:
		SDL_Window* sdlWindow;

		int screenWidth;
		int screenHeight;
	};

}

#endif