#pragma once
#include "Human.h"
#include <OpenGLEngine/InputManager.h>
#include <OpenGLEngine/Camera2D.h>

#include "Bullet.h"

class Gun;

class Player : public Human
{
public:
	Player();
	~Player();

	void Init(float speed, glm::vec2 pos, OpenGLEngine::InputManager* inputManager, OpenGLEngine::Camera2D* camera,	std::vector<Bullet>* bullets);

	void AddGun(Gun* gun);

	void Update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& Zombies) override;

private:

	OpenGLEngine::InputManager* _inputManager;

	std::vector<Gun*> _guns;
	int _currentGunIndex;

	OpenGLEngine::Camera2D* _camera;
	std::vector<Bullet>* _bullets;

};

