#pragma once

#include <string>
#include <vector>

#include <OpenGLEngine/SpriteBatch.h>

const int TILE_WIDTH = 64;

class Level
{
public:
	// Build and load the level
	Level(const std::string& fileName);
	~Level();

	void Draw();

	glm::vec2 GetStartPlayerPos() const { return _startPlayerPos; }
	const std::vector<glm::vec2> GetStartZombiePos() const { return _zombieStartPos; }

	const std::vector<std::string>& GetLevelData() { return _levelData; }

	int GetNumHumans() const { return _numHumans; }

	int GetWidth() const { return _levelData[0].size(); }
	int GetHeight() const { return _levelData.size(); }

private:
	std::vector<std::string> _levelData;
	int _numHumans;
	OpenGLEngine::SpriteBatch _spriteBatch;

	glm::vec2 _startPlayerPos;
	std::vector<glm::vec2> _zombieStartPos;
};

