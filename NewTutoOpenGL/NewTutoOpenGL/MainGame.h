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

	void Run();

private:
	void InitSystem();
	void InitShaders();
	void GameLoop();
	void ProcessInput();
	void DrawGame();

	OpenGLEngine::Window* window;
	int windowWidth;
	int windowHeight;

	GameState currentGameState;

	OpenGLEngine::GLSLProgram* colorProgram;
	OpenGLEngine::Camera2D* camera;

	OpenGLEngine::SpriteBatch spriteBatch;

	OpenGLEngine::InputManager* inputManager;
	OpenGLEngine::FPSLimiter* fpsLimiter;

	float maxFPS;
	float fps;

	float time;
};

#endif