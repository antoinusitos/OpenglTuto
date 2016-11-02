#include "MainGame.h"
#include <Errors.h>
#include <ResourceManager.h>

MainGame::MainGame() : time(0.0f), windowWidth(1024), windowHeight(728), window(nullptr), currentGameState(GameState::PLAY), maxFPS(60.0f)
{
	camera = new OpenGLEngine::Camera2D();
	camera->Init(windowWidth, windowHeight);
}

MainGame::~MainGame()
{
	delete colorProgram;
}

void MainGame::Run()
{
	InitSystem();

	GameLoop();
}

void MainGame::InitSystem()
{
	OpenGLEngine::Init();

	window = new OpenGLEngine::Window();

	window->Create("Game Engine", windowWidth, windowHeight, 0);

	InitShaders();

	spriteBatch.Init();
}

void MainGame::InitShaders()
{
	colorProgram = new OpenGLEngine::GLSLProgram();
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
		// usde for frame time mesuring
		float startTicks = SDL_GetTicks();

		ProcessInput();
		time += 0.01f;

		camera->Update();

		DrawGame();
		CalculateFPS();

		// print only every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10)
		{
			cout << fps << endl;
			frameCounter = 0;
		}

		float frameTicks = SDL_GetTicks() - startTicks;
		// limit the fps to the max fps
		if (1000.0f / maxFPS > frameTicks)
		{
			SDL_Delay(1000.0f / maxFPS - frameTicks);
		}
	}
}

void MainGame::ProcessInput()
{
	SDL_Event theEvent;

	const float CAMERA_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;

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

		case SDL_KEYDOWN:
			switch (theEvent.key.keysym.sym)
			{

			case SDLK_ESCAPE:
				currentGameState = GameState::EXIT;
				break;

			case SDLK_z:
				camera->SetPosition(camera->GetPosition() + glm::vec2(0.0f, CAMERA_SPEED));
				break;

			case SDLK_s:
				camera->SetPosition(camera->GetPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
				break;

			case SDLK_q:
				camera->SetPosition(camera->GetPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
				break;

			case SDLK_d:
				camera->SetPosition(camera->GetPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
				break;

			case SDLK_a:
				camera->SetScale(camera->GetScale() + SCALE_SPEED);
				break;

			case SDLK_e:
				camera->SetScale(camera->GetScale() - SCALE_SPEED);
				break;
			}
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
		OpenGLEngine::FatalError("colorProgram not initialized !");
		return;
	}

	// enable the shader
	colorProgram->Use();
	
	// bind the input of the shader
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, playerTexture.id);
	GLint textureLocation = colorProgram->GetUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	// set the constantly changing time variable
	GLuint timeLocation = colorProgram->GetUniformLocation("time");
	// send the time to the graphic card
	glUniform1f(timeLocation, time);

	// set the camera matrix
	GLuint pLocation = colorProgram->GetUniformLocation("P");
	glm::mat4 cameraMatrix = camera->GetCameraMatrix();

	// send a pointer to the first element in the shader
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	
	spriteBatch.Begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	OpenGLEngine::GLTexture texture = OpenGLEngine::ResourceManager::GetTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Walk1.png");
	OpenGLEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	spriteBatch.Draw(pos, uv, texture.id, 0.0f, color);

	spriteBatch.End();

	spriteBatch.RenderBatch();

	// unbind the input of the shader
	glBindTexture(GL_TEXTURE_2D, 0);
	colorProgram->Unuse();

	window->SwapBuffer();
}

void MainGame::CalculateFPS()
{
	static const int NUM_SAMPLE = 10;
	static float frameTimes[NUM_SAMPLE];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();

	float currentTicks;
	currentTicks = SDL_GetTicks();

	frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLE] = frameTime;

	prevTicks = currentTicks;

	int count;

	currentFrame++;
	if (currentFrame < NUM_SAMPLE)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLE;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; ++i)
	{
		frameTimeAverage += frameTimes[i];
	}

	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		// 1 s / time since last frame
		fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		fps = 60.0f;
	}
}
