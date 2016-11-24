#pragma once
#include <glm.hpp>
#include <vector>
#include <OpenGLEngine/SpriteBatch.h>

class Human;
class Zombie;

const int BULLET_RADIUS = 20;

class Bullet
{
public:
	Bullet(glm::vec2 position, glm::vec2 direction, int damage, float speed);
	~Bullet();

	void Update(std::vector<Human*>& humans,
				std::vector<Zombie*>& Zombies);

	void Draw(OpenGLEngine::SpriteBatch& spriteBatch);

private:

	int _damage;
	glm::vec2 _position;
	glm::vec2 _direction;
	float _speed;
};

