#include "Bullet.h"
#include <OpenGLEngine/ResourceManager.h>

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, int damage, float speed)
{
	_position = position;
	_direction = direction;
	_damage = damage;
	_speed = speed;
}

void Bullet::Update(std::vector<Human*>& humans, std::vector<Zombie*>& Zombies)
{
	_position += _direction * _speed;
}

void Bullet::Draw(OpenGLEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 destRect(_position.x + BULLET_RADIUS, _position.y + BULLET_RADIUS, BULLET_RADIUS / 2, BULLET_RADIUS / 2);
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	OpenGLEngine::Color color;
	color.r = 75;
	color.g = 75;
	color.b = 75;
	color.a = 255;
	spriteBatch.Draw(destRect, uvRect, OpenGLEngine::ResourceManager::GetTexture("Textures/circle.png").id, 0.0f, color);
}

Bullet::~Bullet()
{
}
