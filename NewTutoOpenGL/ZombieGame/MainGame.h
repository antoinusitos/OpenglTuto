#pragma once

#include "SDL.h"
#include "glew.h"

#include <OpenGLEngine/OpenGLEngine.h>

#include <OpenGLEngine/GLTexture.h>
#include <OpenGLEngine/GLSLProgram.h>
#include <OpenGLEngine/Sprite.h>
#include <OpenGLEngine/SpriteBatch.h>
#include <OpenGLEngine/Window.h>
#include <OpenGLEngine/Camera2D.h>
#include <OpenGLEngine/SpriteBatch.h>
#include <OpenGLEngine/InputManager.h>
#include <OpenGLEngine/Timing.h>

#include "Player.h"
#include <vector>
#include "Level.h"
#include "Bullet.h"

enum class GameState
{
	PLAY,
	EXIT,
};

class Zombie;

using namespace std;

class MainGame
{
public:
	MainGame();
	~MainGame();

	/// Run the game
	void Run();

private:
	/// Initializes the core systems
	void InitSystem();

	/// Initializes the level and sets up everything
	void InitLevel();

	/// Initializes the shaders
	void InitShaders();

	/// Main game loop for the program
	void GameLoop();

	/// Update all agents
	void UpdateAgents();

	/// Update all bullets
	void UpdateBullets();

	/// Handles input processing
	void ProcessInput();

	/// renders the game
	void DrawGame();

	/// The game window
	OpenGLEngine::Window* _window;
	int _windowWidth;
	int _windowHeight;

	GameState _currentGameState;

	/// The Shader Program
	OpenGLEngine::GLSLProgram* _textureProgram;

	/// Main Camera
	OpenGLEngine::Camera2D* _camera;

	OpenGLEngine::SpriteBatch _agentSpriteBatch;

	/// The Sprite Batch used to render
	OpenGLEngine::SpriteBatch _spriteBatch;

	/// Handles the Input
	OpenGLEngine::InputManager* _inputManager;

	/// Vector of all levels
	std::vector<Level*> _levels;

	int _currentLevel;

	float _fps;

	Player* _player;
	std::vector<Human*> _humans;
	std::vector<Zombie*> _zombies;
	std::vector<Bullet> _bullets;
};
