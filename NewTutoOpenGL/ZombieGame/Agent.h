#pragma once

#include <glm.hpp>
#include <OpenGLEngine/SpriteBatch.h>

const float AGENT_WIDTH = 60;

class Zombie;
class Human;

class Agent
{
public:
	Agent();
	virtual ~Agent();

	virtual void Update(
		const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& Zombies) = 0;

	void CollideWithLevel(const std::vector<std::string>& levelData);

	void Draw(OpenGLEngine::SpriteBatch& spriteBatch);

	glm::vec2 GetPosition() const { return _position; }

protected:

	void CheckTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePositions, float x, float y);

	void CollideWithTile(glm::vec2 tilePos);

	glm::vec2 _position;
	OpenGLEngine::Color _color;
	float _speed;
};

