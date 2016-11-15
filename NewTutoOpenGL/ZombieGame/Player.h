#pragma once
#include "Human.h"
#include <OpenGLEngine/InputManager.h>

class Player : public Human
{
public:
	Player();
	~Player();

	void Init(float speed, glm::vec2 pos, OpenGLEngine::InputManager* inputManager);

	void Update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& Zombies);

private:

	OpenGLEngine::InputManager* _inputManager;

};

