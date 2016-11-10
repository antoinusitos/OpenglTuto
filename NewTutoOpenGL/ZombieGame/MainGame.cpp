#include "MainGame.h"
#include <OpenGLEngine/Errors.h>
#include <OpenGLEngine/ResourceManager.h>

MainGame::MainGame() : _window(nullptr), _windowWidth(1024), _windowHeight(728), _currentGameState(GameState::PLAY)
{
	_camera = new OpenGLEngine::Camera2D();
	_camera->Init(_windowWidth, _windowHeight);
}

MainGame::~MainGame()
{
	delete _textureProgram;
	delete _inputManager;
}

void MainGame::Run()
{
	InitSystem();

	GameLoop();
}

void MainGame::InitSystem()
{
	OpenGLEngine::Init();

	_window = new OpenGLEngine::Window();

	_window->Create("Game Engine", _windowWidth, _windowHeight, 0);

	InitShaders();

	_spriteBatch.Init();

	_inputManager = new OpenGLEngine::InputManager();
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
	while (_currentGameState != GameState::EXIT)
	{
		ProcessInput();
		_camera->Update();
		DrawGame();
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

	// Drawn code goes here

	
	// Swap our buffer and draw everything to the screen
	_window->SwapBuffer();
}