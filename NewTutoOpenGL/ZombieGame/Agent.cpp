#include "Agent.h"
#include <OpenGLEngine/ResourceManager.h>
#include "Level.h"

Agent::Agent()
{
}


Agent::~Agent()
{
}

void Agent::CollideWithLevel(const std::vector<std::string>& levelData)
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

	// Do the collisions
	for (int i = 0; i < collideTilePositions.size(); ++i)
	{
		CollideWithTile(collideTilePositions[i]);
	}
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

void Agent::CheckTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePositions, float x, float y)
{
	glm::vec2 cornerPos = glm::vec2(
		floor(x / (float)TILE_WIDTH),
		floor(y / (float)TILE_WIDTH));

	if (levelData[cornerPos.y][cornerPos.x] != '.')
	{
		collideTilePositions.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
	}

}

// AABB collisions
void Agent::CollideWithTile(glm::vec2 tilePos)
{
	const float agentRadius = (float)AGENT_WIDTH / 2.0f;
	const float tileRadius = (float)TILE_WIDTH / 2.0f;
	const float minDistance = agentRadius + tileRadius;

	// Vector from tile to agent
	glm::vec2 distVec = _position - tilePos;

	float xDepth = minDistance - distVec.x;
	float yDepth = minDistance - distVec.y;

	float absXDepth = abs(xDepth);
	float absYDepth = abs(yDepth);

	if (xDepth > 0 || yDepth > 0)
	{
		if (absXDepth < absYDepth)
		{
			_position += xDepth;
		}
		else
		{
			_position += yDepth;
		}
	}
}
