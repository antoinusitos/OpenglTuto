#include "MainGame.h"
#include <OpenGLEngine/Errors.h>
#include <OpenGLEngine/OpenGLEngine.h>
#include <OpenGLEngine/ResourceManager.h>
#include <iostream>
#include <OpenGLEngine/Timing.h>
#include "Zombie.h"
#include <random>
#include <ctime>
#include "Gun.h"

const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 1.3f;
const float PLAYER_SPEED = 5.0f;

MainGame::MainGame() : _window(nullptr), _windowWidth(1024), _windowHeight(768), _currentGameState(GameState::PLAY), _fps(0), _player(nullptr), _numHumansKilled(0), _numZombiesKilled(0)
{
	_camera = new OpenGLEngine::Camera2D();
	_camera->Init(_windowWidth, _windowHeight);
}

MainGame::~MainGame()
{
	delete _textureProgram;
	delete _inputManager;
	delete _camera;

	for (int i = 0; i < _levels.size(); ++i)
	{
		delete _levels[i];
	}
}

void MainGame::Run()
{
	InitSystem();
	InitLevel();
	GameLoop();
}

void MainGame::InitSystem()
{
	OpenGLEngine::Init();

	_window = new OpenGLEngine::Window();

	_window->Create("Game Engine", _windowWidth, _windowHeight, 0);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	InitShaders();

	_agentSpriteBatch.Init();

	_camera->Init(_windowWidth, _windowHeight);
	_inputManager = new OpenGLEngine::InputManager();

}

void MainGame::InitLevel()
{
	// Level 1
	_levels.push_back(new Level("Levels/Level1.txt"));
	_currentLevel = 0;

	_player = new Player();
	_player->Init(PLAYER_SPEED, _levels[_currentLevel]->GetStartPlayerPos(), _inputManager, _camera, &_bullets);

	_humans.push_back(_player);

	std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->GetWidth() - 2);
	std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->GetHeight() - 2);

	// Add all random humans
	for (int i = 0; i < _levels[_currentLevel]->GetNumHumans(); ++i)
	{
		_humans.push_back(new Human);

		glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
		_humans.back()->Init(HUMAN_SPEED, pos);
	}

	// Add all the zombies
	const std::vector<glm::vec2>& zombiePositions = _levels[_currentLevel]->GetStartZombiePos();
	for (int i = 0; i < zombiePositions.size(); ++i)
	{
		_zombies.push_back(new Zombie);
		_zombies.back()->Init(ZOMBIE_SPEED, zombiePositions[i]);
	}

	// Set up the players gun
	const float BULLET_SPEED = 20.0f;
	_player->AddGun(new Gun("Magnum", 10, 1, 5.0f, BULLET_SPEED, 30));
	_player->AddGun(new Gun("ShotGun", 30, 12, 20.0f, BULLET_SPEED, 4));
	_player->AddGun(new Gun("MP5", 2, 1, 10.0f, BULLET_SPEED, 20));
}

void MainGame::UpdateAgents()
{
	// Update all humans
	for (int i = 0; i < _humans.size(); ++i)
	{
		_humans[i]->Update(_levels[_currentLevel]->GetLevelData(), _humans, _zombies);
	}
	
	// Update all humans
	for (int i = 0; i < _zombies.size(); ++i)
	{
		_zombies[i]->Update(_levels[_currentLevel]->GetLevelData(), _humans, _zombies);
	}
	
	// Update zimbies collisions
	for (int i = 0; i < _zombies.size(); ++i)
	{
		// Collide with other zombies
		for (int j = i + 1; j < _zombies.size(); ++j)
		{
			_zombies[i]->CollideWithAgent(_zombies[j]);
		}
		// Collide with humans
		for (int j = 1; j < _humans.size(); ++j)
		{
			if(_zombies[i]->CollideWithAgent(_humans[j]))
			{
				// Add the new zombie
				_zombies.push_back(new Zombie);
				_zombies.back()->Init(ZOMBIE_SPEED, _humans[j]->GetPosition());
				// Delete the human
				delete _humans[j];
				_humans[j] = _humans.back();
				_humans.pop_back();
			}
		}

		// Collide with player
		if(_zombies[i]->CollideWithAgent(_player))
		{
			OpenGLEngine::FatalError("YOU LOOSE");
		}
	}

	// Update humans collisions
	for (int i = 0; i < _humans.size(); ++i)
	{
		// Collide with other humans
		for (int j = i + 1; j < _humans.size(); ++j)
		{
			_humans[i]->CollideWithAgent(_humans[j]);
		}
	}
}

void MainGame::UpdateBullets()
{
	// update and collide with world
	for (int i = 0; i < _bullets.size();)
	{
		// if update returns true, the bullet collided with a wall
		if (_bullets[i].Update(_levels[_currentLevel]->GetLevelData()))
		{
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}
		else
		{
			++i;
		}
	}

	bool wasBulletRemoved;

	// collide with humans and zombies
	for (int i = 0; i < _bullets.size(); i++)
	{
		wasBulletRemoved = false;
		// Loop through zombies
		for (int j = 0; j < _zombies.size();)
		{
			if (_bullets[i].CollideWithAgent(_zombies[j]))
			{

				// Damage zombie, and kill it if its out of health
				if (_zombies[j]->ApplyDamage(_bullets[i].GetDamage()))
				{
					delete _zombies[j];
					_numZombiesKilled++;
					_zombies[j] = _zombies.back();
					_zombies.pop_back();
				}
				else
				{
					j++;
				}

				// remove the bullet
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
				wasBulletRemoved = true;
				// the bullet is destory, stop iterating through zombies
				break;
			}
			else
			{
				j++;
			}
		}

		// Loop through humans
		if (!wasBulletRemoved)
		{
			//j = 0 is the player
			for (int j = 1; j < _humans.size();)
			{
				if (_bullets[i].CollideWithAgent(_humans[j]))
				{

					// Damage human, and kill it if its out of health
					if (_humans[j]->ApplyDamage(_bullets[i].GetDamage()))
					{
						delete _humans[j];
						_numHumansKilled++;
						_humans[j] = _humans.back();
						_humans.pop_back();
					}
					else
					{
						j++;
					}

					// remove the bullet
					_bullets[i] = _bullets.back();
					_bullets.pop_back();
					wasBulletRemoved = true;
					// the bullet is destory, stop iterating through zombies
					break;
				}
				else
				{
					j++;
				}
			}
		}
	}
}

void MainGame::CheckVictory()
{
	// TODO : Support for multiple levels
	// if all zombies are dead we win
	if (_zombies.empty())
	{
		std::printf("*** You win ! ***\n Tou killed %d humans and %d zombies. There are %d/%d civilians remaining", _numHumansKilled, _numZombiesKilled, _humans.size() - 1, _levels[_currentLevel]->GetNumHumans());
		FatalError("");
	}
}

void MainGame::InitShaders()
{
	_textureProgram = new OpenGLEngine::GLSLProgram();
	_textureProgram->CompileShaders("Shaders/ColorShading.vert", "Shaders/ColorShading.frag");
	_textureProgram->AddAttribute("vertexPosition");
	_textureProgram->AddAttribute("vertexColor");
	_textureProgram->AddAttribute("vertexUV");
	_textureProgram->LinkShaders();
}

void MainGame::GameLoop()
{
	OpenGLEngine::FPSLimiter fpsLimiter;
	fpsLimiter.SetMaxFPS(60.0f);

	while (_currentGameState != GameState::EXIT)
	{
		fpsLimiter.Begin();

		CheckVictory();

		ProcessInput();
		
		UpdateAgents();

		UpdateBullets();

		_camera->SetPosition(_player->GetPosition());

		_camera->Update();

		DrawGame();

		fpsLimiter.End();
	}
}

void MainGame::ProcessInput()
{
	SDL_Event theEvent;

	while (SDL_PollEvent(&theEvent))
	{
		switch (theEvent.type)
		{
		case SDL_QUIT:
			_currentGameState = GameState::EXIT;
			break;

		case SDL_MOUSEMOTION:
			_inputManager->SetMouseCoord(theEvent.motion.x, theEvent.motion.y);
			break;

		case SDL_KEYDOWN:
			_inputManager->PressKey(theEvent.key.keysym.sym);
			break;

		case SDL_KEYUP:
			_inputManager->ReleasedKey(theEvent.key.keysym.sym);
			break;

		case SDL_MOUSEBUTTONDOWN:
			_inputManager->PressKey(theEvent.button.button);
			break;

		case SDL_MOUSEBUTTONUP:
			_inputManager->ReleasedKey(theEvent.button.button);
			break;

		}
		
	}

	if (_inputManager->isKeyPressed(SDLK_ESCAPE))
	{
		_currentGameState = GameState::EXIT;
	}
}

void MainGame::DrawGame()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_textureProgram->Use();

	// Drawn code goes here
	glActiveTexture(GL_TEXTURE0);

	//Make sure the shader uses texture 0
	GLint textureUniform = _textureProgram->GetUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	// Grab the camera matrix
	glm::mat4 projectionMatrix = _camera->GetCameraMatrix();
	GLint PUniform = _textureProgram->GetUniformLocation("P");
	glUniformMatrix4fv(PUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	// Draw the level
	_levels[_currentLevel]->Draw();

	_agentSpriteBatch.Begin();

	// Draw the humans
	for (int i = 0; i < _humans.size(); ++i)
	{
		_humans[i]->Draw(_agentSpriteBatch);
	}

	// Draw the zombies
	for (int i = 0; i < _zombies.size(); ++i)
	{
		_zombies[i]->Draw(_agentSpriteBatch);
	}

	// Draw the bullets
	for (int i = 0; i < _bullets.size(); ++i)
	{
		_bullets[i].Draw(_agentSpriteBatch);
	}

	_agentSpriteBatch.End();

	_agentSpriteBatch.RenderBatch();

	_textureProgram->Unuse();
	
	// Swap our buffer and draw everything to the screen
	_window->SwapBuffer();
}