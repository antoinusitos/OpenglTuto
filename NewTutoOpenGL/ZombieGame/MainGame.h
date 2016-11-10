#ifndef DEF_MAINGAME
#define DEF_MAINGAME

#include "SDL.h"
#include "glew.h"

#include <OpenGLEngine/OpenGLEngine.h>

#include <OpenGLEngine/GLTexture.h>
#include <OpenGLEngine/GLSLProgram.h>
#include <OpenGLEngine/Sprite.h>
#include <OpenGLEngine/Window.h>
#include <OpenGLEngine/Camera2D.h>
#include <OpenGLEngine/SpriteBatch.h>
#include <OpenGLEngine/InputManager.h>
#include <OpenGLEngine/Timing.h>

#include <vector>

enum class GameState
{
	PLAY,
	EXIT,
};

using namespace std;

class MainGame
{
public:
	MainGame();
	~MainGame();

	// Run the game
	void Run();

private:
	// Initializes the core systems
	void InitSystem();

	// Initializes the shaders
	void InitShaders();

	// Main game loop for the program
	void GameLoop();

	// Handles input processing
	void ProcessInput();

	// renders the game
	void DrawGame();

	// The game window
	OpenGLEngine::Window* _window;
	int _windowWidth;
	int _windowHeight;

	GameState _currentGameState;

	// The Shader Program
	OpenGLEngine::GLSLProgram* _textureProgram;

	// Main Camera
	OpenGLEngine::Camera2D* _camera;

	// The Sprite Batch used to render
	OpenGLEngine::SpriteBatch _spriteBatch;

	// Handles the Input
	OpenGLEngine::InputManager* _inputManager;
};

#endif