#include "MainGame.h"

int main(int argc, char** argv)
{
	MainGame* mainGame = new MainGame();
	mainGame->Run();

	delete mainGame;

	return 0;

}