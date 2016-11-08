#include "Bullet.h"
#include <OpenGLEngine/ResourceManager.h>


Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float s, int theLifeTime)
{
	position = pos;
	direction = dir;
	speed = s;
	lifeTime = theLifeTime;
}


Bullet::~Bullet()
{
}

void Bullet::Draw(OpenGLEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	OpenGLEngine::GLTexture texture = OpenGLEngine::ResourceManager::GetTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Walk1.png");
	OpenGLEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 posAndSize = glm::vec4(position.x, position.y, 30, 30);

	spriteBatch.Draw(posAndSize, uv, texture.id, 0.0f, color);
}

bool Bullet::Update()
{
	position += direction * speed;
	lifeTime--;
	if (lifeTime == 0)
	{
		return true;
	}
	return false;
}
