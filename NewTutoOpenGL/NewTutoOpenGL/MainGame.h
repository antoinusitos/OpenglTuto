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
	void CalculateFPS();

	OpenGLEngine::Window* window;
	int windowWidth;
	int windowHeight;

	GameState currentGameState;

	OpenGLEngine::GLSLProgram* colorProgram;
	OpenGLEngine::Camera2D* camera;

	OpenGLEngine::SpriteBatch spriteBatch;

	float fps;
	float frameTime;
	float maxFPS;

	float time;
};

#endif