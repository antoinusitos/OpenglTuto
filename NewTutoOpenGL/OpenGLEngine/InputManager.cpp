#include "InputManager.h"

namespace OpenGLEngine
{

	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::PressKey(unsigned int keyID)
	{
		keyMap[keyID] = true;
	}

	void InputManager::ReleasedKey(unsigned int keyID)
	{
		keyMap[keyID] = false;
	}

	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		auto it = keyMap.find(keyID);
		if (it != keyMap.end())
		{
			return it->second;
		}
		else
		{
			return false;
		}
	}

}