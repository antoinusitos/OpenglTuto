#include "Player.h"
#include <SDL.h>
#include "Gun.h"

Player::Player()
{
	_currentGunIndex = -1;
	_inputManager = nullptr;
	_camera = nullptr;
}


Player::~Player()
{
}

void Player::Init(float speed, glm::vec2 pos, OpenGLEngine::InputManager* inputManager, OpenGLEngine::Camera2D* camera, std::vector<Bullet>* bullets)
{
	_speed = speed;
	_position = pos;
	_color.r = 0;
	_color.g = 0;
	_color.b = 185;
	_color.a = 255;
	_inputManager = inputManager;
	_camera = camera;
	_bullets = bullets;
}

void Player::AddGun(Gun* gun)
{
	// Add the gun to the inventory
	_guns.push_back(gun);
	
	// If no gun equipped, equip gun
	if(_currentGunIndex == -1)
	{
		_currentGunIndex = 0;
	}
}

void Player::Update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& Zombies)
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

	if (_inputManager->isKeyPressed(SDLK_1) && _guns.size() >= 0)
	{
		_currentGunIndex = 0;
	}
	else if (_inputManager->isKeyPressed(SDLK_2) && _guns.size() >= 1)
	{
		_currentGunIndex = 1;
	}
	else if (_inputManager->isKeyPressed(SDLK_3) && _guns.size() >= 2)
	{
		_currentGunIndex = 2;
	}

	if(_currentGunIndex != -1)
	{
		glm::vec2 mouseCoords = _inputManager->GetMouseCoord();
		mouseCoords = _camera->ConvertScreenToWorld(mouseCoords);

		glm::vec2 playerPos = _position + glm::vec2(AGENT_RADIUS);

		glm::vec2 direction = glm::normalize(mouseCoords - playerPos);

		_guns[_currentGunIndex]->Update(
			_inputManager->isKeyPressed(SDL_BUTTON_LEFT),
			playerPos,
			direction,
			*_bullets);
	}

	CollideWithLevel(levelData);
}
