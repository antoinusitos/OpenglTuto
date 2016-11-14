#include "Level.h"

#include <fstream>
#include <iostream>

#include <OpenGLEngine/Errors.h>
#include <OpenGLEngine/ResourceManager.h>

Level::Level(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);

	// Error checking
	if(file.fail())
	{
		OpenGLEngine::FatalError("Failed to open " + fileName);
	}

	// Throw away the first string in tmp
	std::string temp;
	file >> temp >> _numHumans;

	while(std::getline(file, temp))
	{
		_levelData.push_back(temp);
	}

	_spriteBatch.Init();
	_spriteBatch.Begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	OpenGLEngine::Color whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;

	// Render all the tiles
	for (int y = 0; y < _levelData.size(); ++y)
	{
		for (int x = 0; x < _levelData[y].size(); ++x)
		{
			// Brab the tile
			char tile = _levelData[y][x];

			// Get dest Rect
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			// Process the tile
			switch (tile)
			{
			case 'R':
				_spriteBatch.Draw(
					destRect,
					uvRect,
					OpenGLEngine::ResourceManager::GetTexture("Textures/red_brick.png").id,
					0.0f,
					whiteColor);
				break;
			case 'G':
				_spriteBatch.Draw(
					destRect,
					uvRect,
					OpenGLEngine::ResourceManager::GetTexture("Textures/glass.png").id,
					0.0f,
					whiteColor);
				break;
			case 'L':
				_spriteBatch.Draw(
					destRect,
					uvRect,
					OpenGLEngine::ResourceManager::GetTexture("Textures/light_brick.png").id,
					0.0f,
					whiteColor);
				break;
			case '@':
				_startPlayerPos.x = x * TILE_WIDTH;
				_startPlayerPos.y = y * TILE_WIDTH;
				break;
			case 'Z':
				_zombieStartPos.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
				break;

			case '.':
				break;

			default:
				std::printf("Unexepected symbol %c at (%d,%d)", tile, x, y);
				break;
			}

		}
	}
	_spriteBatch.End();
}


Level::~Level()
{
}

void Level::Draw()
{
	_spriteBatch.RenderBatch();
}
