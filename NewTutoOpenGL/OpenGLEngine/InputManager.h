#ifndef DEF_INPUTMANAGER
#define DEF_INPUTMANAGER

#include <unordered_map>

namespace OpenGLEngine
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void PressKey(unsigned int keyID);
		void ReleasedKey(unsigned int keyID);

		bool isKeyPressed(unsigned int keyID);

	private:
		std::unordered_map<unsigned int, bool> keyMap;
	};
}

#endif