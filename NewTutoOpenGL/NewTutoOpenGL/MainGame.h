#ifndef DEF_MAINGAME
#define DEF_MAINGAME

#include "SDL.h"
#include "glew.h"

#include "UserIncludes.h"
#include "GLTexture.h"

#include "Sprite.h"
#include "GLSLProgram.h"

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

	SDL_Window* window;
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