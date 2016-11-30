#include "Bullet.h"
#include <OpenGLEngine/ResourceManager.h>

#include "Agent.h"
#include "Human.h"
#include "Zombie.h"
#include "Level.h"

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, int damage, float speed)
{
	_position = position;
	_direction = direction;
	_damage = damage;
	_speed = speed;
}

Bullet::~Bullet()
{
}

bool Bullet::Update(const std::vector<std::string>& levelData)
{
	_position += _direction * _speed;

	return CollideWithWorld(levelData);
}

void Bullet::Draw(OpenGLEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 destRect(_position.x + BULLET_RADIUS, _position.y + BULLET_RADIUS, BULLET_RADIUS * 2, BULLET_RADIUS * 2);
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	OpenGLEngine::Color color;
	color.r = 75;
	color.g = 75;
	color.b = 75;
	color.a = 255;
	spriteBatch.Draw(destRect, uvRect, OpenGLEngine::ResourceManager::GetTexture("Textures/circle.png").id, 0.0f, color);
}

bool Bullet::CollideWithAgent(Agent* agent)
{
	const float MIN_DISTANCE = AGENT_RADIUS + BULLET_RADIUS;

	glm::vec2 centerPosA = _position;
	glm::vec2 centerPosB = agent->GetPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;

	// We have a collision
	if (collisionDepth > 0)
	{
		return true;
	}
	return false;
}

const int Bullet::GetDamage()
{
	return _damage;
}

bool Bullet::CollideWithWorld(const std::vector<std::string>& levelData)
{
	glm::ivec2 gridPosition;
	gridPosition.x = floor(_position.x / (float)TILE_WIDTH);
	gridPosition.y = floor(_position.y / (float)TILE_WIDTH);

	// If we are outside the world, return;
	if (gridPosition.x < 0 || gridPosition.x > levelData[0].length() ||
		gridPosition.y < 0 || gridPosition.x > levelData.size())
	{
		return true;
	}

	return(levelData[gridPosition.y][gridPosition.x] != '.');
}
