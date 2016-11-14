#include "Player.h"
#include <SDL.h>


Player::Player()
{
}


Player::~Player()
{
}

void Player::Init(float speed, glm::vec2 pos, OpenGLEngine::InputManager* inputManager)
{
	_speed = speed;
	_position = pos;
	_color.r = 0;
	_color.g = 0;
	_color.b = 185;
	_color.a = 255;
	_inputManager = inputManager;
}

void Player::Update()
{
	if(_inputManager->isKeyPressed(SDLK_d))
	{
		_position.x += _speed;
	}
	else if (_inputManager->isKeyPressed(SDLK_q))
	{
		_position.x -= _speed;
	}

	if (_inputManager->isKeyPressed(SDLK_s))
	{
		_position.y -= _speed;
	}
	else if (_inputManager->isKeyPressed(SDLK_z))
	{
		_position.y += _speed;
	}
}
