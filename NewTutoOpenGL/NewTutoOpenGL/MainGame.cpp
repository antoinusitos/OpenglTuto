#include "MainGame.h"
#include <OpenGLEngine/Errors.h>
#include <OpenGLEngine/ResourceManager.h>

MainGame::MainGame() : time(0.0f), windowWidth(1024), windowHeight(728), window(nullptr), currentGameState(GameState::PLAY), maxFPS(60.0f)
{
	camera = new OpenGLEngine::Camera2D();
	camera->Init(windowWidth, windowHeight);
}

MainGame::~MainGame()
{
	delete colorProgram;
	delete inputManager;
	delete fpsLimiter;
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

	inputManager = new OpenGLEngine::InputManager();
	fpsLimiter = new OpenGLEngine::FPSLimiter();
	fpsLimiter->Init(maxFPS);
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
		fpsLimiter->Begin();

		ProcessInput();
		time += 0.01f;

		camera->Update();

		DrawGame();

		fps = fpsLimiter->End();

		// print only every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10)
		{
			cout << fps << endl;
			frameCounter = 0;
		}
	}
}

void MainGame::ProcessInput()
{
	SDL_Event theEvent;

	const float CAMERA_SPEED = 2.0f;
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
			inputManager->PressKey(theEvent.key.keysym.sym);
			break;

		case SDL_KEYUP:
			inputManager->ReleasedKey(theEvent.key.keysym.sym);
			break;
		}
		
	}

	if (inputManager->isKeyPressed(SDLK_ESCAPE))
	{
		currentGameState = GameState::EXIT;
	}

	if (inputManager->isKeyPressed(SDLK_z))
	{
		camera->SetPosition(camera->GetPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}

	if (inputManager->isKeyPressed(SDLK_s))
	{
		camera->SetPosition(camera->GetPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}

	if (inputManager->isKeyPressed(SDLK_q))
	{
		camera->SetPosition(camera->GetPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}

	if (inputManager->isKeyPressed(SDLK_d))
	{
		camera->SetPosition(camera->GetPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}

	if (inputManager->isKeyPressed(SDLK_a))
	{
		camera->SetScale(camera->GetScale() + SCALE_SPEED);
	}

	if (inputManager->isKeyPressed(SDLK_e))
	{
		camera->SetScale(camera->GetScale() - SCALE_SPEED);
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
	spriteBatch.Draw(pos + glm::vec4(50, 0, 0, 0), uv, texture.id, 0.0f, color);


	spriteBatch.End();

	spriteBatch.RenderBatch();

	// unbind the input of the shader
	glBindTexture(GL_TEXTURE_2D, 0);
	colorProgram->Unuse();

	window->SwapBuffer();
}