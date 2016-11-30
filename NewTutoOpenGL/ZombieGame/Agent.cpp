#include "Agent.h"
#include <OpenGLEngine/ResourceManager.h>
#include "Level.h"
#include <algorithm>

Agent::Agent()
{
}


Agent::~Agent()
{
}

bool Agent::CollideWithLevel(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePositions;

	// Check the four corners
	// first corner
	CheckTilePosition(levelData, collideTilePositions, _position.x, _position.y);

	// second corner
	CheckTilePosition(levelData, collideTilePositions, _position.x + AGENT_WIDTH, _position.y);

	// third corner
	CheckTilePosition(levelData, collideTilePositions, _position.x, _position.y + AGENT_WIDTH);

	// fourth corner
	CheckTilePosition(levelData, collideTilePositions, _position.x + AGENT_WIDTH, _position.y + AGENT_WIDTH);

	if(collideTilePositions.size() == 0)
	{
		return false;
	}

	// Do the collisions
	for (int i = 0; i < collideTilePositions.size(); ++i)
	{
		CollideWithTile(collideTilePositions[i]);
	}

	return true;
}

bool Agent::CollideWithAgent(Agent* agent)
{
	const float MIN_DISTANCE = AGENT_RADIUS * 2.0f ;

	glm::vec2 centerPosA = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 centerPosB = agent->GetPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;

	// We have a collision
	if(collisionDepth > 0)
	{
		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;

		_position += collisionDepthVec / 2.0f;
		agent->_position -= collisionDepthVec / 2.0f;
		return true;
	}
	return false;
}
void Agent::Draw(OpenGLEngine::SpriteBatch& spriteBatch)
{
	static int textureID = OpenGLEngine::ResourceManager::GetTexture("Textures/circle.png").id;

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	spriteBatch.Draw(destRect, uvRect, textureID, 0.0f, _color);
}

bool Agent::ApplyDamage(int damage)
{
	_health -= damage;
	if (_health <= 0)
	{
		return true;
	}
	return false;
}

void Agent::CheckTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePositions, float x, float y)
{
	glm::vec2 cornerPos = glm::vec2(
		floor(x / (float)TILE_WIDTH),
		floor(y / (float)TILE_WIDTH));

	// If we are outside the world, return;
	if (cornerPos.x < 0 || cornerPos.x > levelData[0].length() ||
		cornerPos.y < 0 || cornerPos.x > levelData.size())
	{
		return;
	}

	if (levelData[cornerPos.y][cornerPos.x] != '.')
	{
		collideTilePositions.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
	}

}

// AABB collisions
void Agent::CollideWithTile(glm::vec2 tilePos)
{
	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	// Vector from tile to agent
	glm::vec2 centerPlayerPos = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerPlayerPos - tilePos;

	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);

	// if this is true, we are colliding
	if (xDepth > 0 || yDepth > 0)
	{
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f))
		{
			if(distVec.x < 0)
				_position.x -= xDepth;
			else
				_position.x += xDepth;
		}
		else
		{
			if (distVec.y < 0)
				_position.y -= yDepth;
			else
				_position.y += yDepth;
		}
	}
}
