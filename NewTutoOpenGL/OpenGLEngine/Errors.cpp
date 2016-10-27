#include "Errors.h"
#include "SDL.h"

namespace OpenGLEngine
{

	void FatalError(string errorString)
	{
		cout << errorString << endl;
		cout << "Enter any key to quit...";
		int tmp;
		cin >> tmp;
		SDL_Quit();
		exit(1);
	}

}