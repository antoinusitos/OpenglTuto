#ifndef DEF_INPUTMANAGER
#define DEF_INPUTMANAGER

#include <unordered_map>
#include <glm.hpp>

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

		void SetMouseCoord(float xPos, float yPos);
		glm::vec2 GetMouseCoord() const { return mouseCoord; }

	private:
		std::unordered_map<unsigned int, bool> keyMap;

		glm::vec2 mouseCoord;
	};
}

#endif