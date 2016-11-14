#pragma once
#include "Human.h"
#include <OpenGLEngine/InputManager.h>

class Player : public Human
{
public:
	Player();
	~Player();

	void Init(float speed, glm::vec2 pos, OpenGLEngine::InputManager* inputManager);

	void Update();

private:

	OpenGLEngine::InputManager* _inputManager;

};

