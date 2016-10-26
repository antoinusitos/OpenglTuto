#include "MainGame.h"
#include "Errors.h"

MainGame::MainGame() : time(0.0f), windowWidth(1024), windowHeight(728), window(nullptr), currentGameState(GameState::PLAY)
{
}

MainGame::~MainGame()
{
	for (int i = 0; i < sprites.size(); ++i)
	{
		delete sprites[i];
	}
	delete colorProgram;
}

void MainGame::Run()
{
	InitSystem();

	sprites.push_back(new Sprite());
	sprites.back()->Init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	sprites.push_back(new Sprite());
	sprites.back()->Init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	GameLoop();
}

void MainGame::InitSystem()
{
	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// create the window
	window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);

	if (window == nullptr)
	{
		FatalError("SDL Window could not be created!");
	}

	// create a context for the window
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr)
	{
		FatalError("SDL_GL Context could not be created!");
	}

	// init glew
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		FatalError("could not be initialize glew!");
	}

	// init sdl
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// put a blue clear screen
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	InitShaders();
}

void MainGame::InitShaders()
{
	colorProgram = new GLSLProgram();
	colorProgram->CompileShaders("Shaders/ColorShading.vert", "Shaders/ColorShading.frag");
	colorProgram->AddAttribute("vertexPosition");
	colorProgram->AddAttribute("vertexColor");
	colorProgram->AddAttribute("vertexUV");
	colorProgram->LinkShaders();
}

void MainGame::GameLoop()
{
	while (currentGameState != GameState::EXIT)
	{
		ProcessInput();
		time += 0.01f;
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
			currentGameState = GameState::EXIT;
			break;

		case SDL_MOUSEMOTION:
			//cout << theEvent.motion.x << " " << theEvent.motion.y << endl;
			break;
		}
		switch (theEvent.key.keysym.scancode)
		{

		case SDL_SCANCODE_ESCAPE:
			currentGameState = GameState::EXIT;
			break;
		}
	}
}

void MainGame::DrawGame()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	//clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!colorProgram)
	{
		FatalError("colorProgram not initialized !");
		return;
	}

	// bind the input of the shader
	colorProgram->Use();
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, playerTexture.id);
	GLint textureLocation = colorProgram->GetUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLuint timeLocation = colorProgram->GetUniformLocation("time");
	// send the time to the graphic card
	glUniform1f(timeLocation, time);

	// draw the sprites
	for (int i = 0; i < sprites.size(); ++i)
	{
		sprites[i]->Draw();
	}

	// unbind the input of the shader
	glBindTexture(GL_TEXTURE_2D, 0);
	colorProgram->Unuse();

	// swap the buffer and draw everything
	SDL_GL_SwapWindow(window);
}