#include "MainGame.h"
#include <OpenGLEngine/Errors.h>
#include <OpenGLEngine/OpenGLEngine.h>
#include <OpenGLEngine/ResourceManager.h>
#include <iostream>
#include <OpenGLEngine/Timing.h>
#include "Zombie.h"
#include <random>
#include <ctime>

MainGame::MainGame() : _window(nullptr), _windowWidth(1024), _windowHeight(768), _currentGameState(GameState::PLAY), _fps(0), _player(nullptr)
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
	_player->Init(4.0f, _levels[_currentLevel]->GetStartPlayerPos(), _inputManager);

	_humans.push_back(_player);

	std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->GetWidth() - 2);
	std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->GetHeight() - 2);

	const float HUMAN_SPEED = 1.0f;

	// Add all random humans
	for (int i = 0; i < _levels[_currentLevel]->GetNumHumans(); ++i)
	{
		_humans.push_back(new Human);

		glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
		_humans.back()->Init(HUMAN_SPEED, pos);
	}
}

void MainGame::UpdateAgents()
{
	// Update all humans
	for (int i = 0; i < _humans.size(); ++i)
	{
		_humans[i]->Update(_levels[_currentLevel]->GetLevelData(), _humans, _zombies);
	}

	// Update collisions
	for (int i = 0; i < _humans.size(); ++i)
	{
		for (int j = i + 1; j < _humans.size(); ++j)
		{
			_humans[i]->CollideWithAgent(_humans[j]);
		}
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

		ProcessInput();
		
		UpdateAgents();

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

	_agentSpriteBatch.End();

	_agentSpriteBatch.RenderBatch();

	_textureProgram->Unuse();
	
	// Swap our buffer and draw everything to the screen
	_window->SwapBuffer();
}