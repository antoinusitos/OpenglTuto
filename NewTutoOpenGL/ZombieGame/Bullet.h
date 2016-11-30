#pragma once
#include <glm.hpp>
#include <vector>
#include <OpenGLEngine/SpriteBatch.h>

class Human;
class Zombie;
class Agent;

const int BULLET_RADIUS = 5;

class Bullet
{
public:
	Bullet(glm::vec2 position, glm::vec2 direction, int damage, float speed);
	~Bullet();

	// when return true, delete the bullet
	bool Update(const std::vector<std::string>& levelData);

	void Draw(OpenGLEngine::SpriteBatch& spriteBatch);

	bool CollideWithAgent(Agent* agent);

	const int GetDamage();

private:

	bool CollideWithWorld(const std::vector<std::string>& levelData);

	int _damage;
	glm::vec2 _position;
	glm::vec2 _direction;
	float _speed;
};

