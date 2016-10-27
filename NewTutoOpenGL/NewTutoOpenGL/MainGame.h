#ifndef DEF_MAINGAME
#define DEF_MAINGAME

#include "SDL.h"
#include "glew.h"

#include <OpenGLEngine/OpenGLEngine.h>

#include <OpenGLEngine/GLTexture.h>
#include <OpenGLEngine/GLSLProgram.h>
#include <OpenGLEngine/Sprite.h>
#include <OpenGLEngine/Window.h>

#include <vector>

using namespace std;
using namespace OpenGLEngine;

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

	Window* window;
	int windowWidth;
	int windowHeight;

	GameState currentGameState;

	vector<Sprite*> sprites;

	GLSLProgram* colorProgram;

	float fps;
	float frameTime;
	float maxFPS;

	float time;
};

#endif