#include "Timing.h"

#include <SDL.h>

namespace OpenGLEngine
{

	FPSLimiter::FPSLimiter()
	{
	}


	FPSLimiter::~FPSLimiter()
	{
	}

	void FPSLimiter::Init(float theTargetFPS)
	{
		SetMaxFPS(theTargetFPS);
	}

	void FPSLimiter::SetMaxFPS(float theTargetFPS)
	{
		maxFPS = theTargetFPS;
	}

	void FPSLimiter::Begin()
	{
		// use for frame time mesuring
		startTicks = SDL_GetTicks();
	}

	float FPSLimiter::End()
	{
		CalculateFPS();

		float frameTicks = SDL_GetTicks() - startTicks;
		// limit the fps to the max fps
		if (1000.0f / maxFPS > frameTicks)
		{
			SDL_Delay(1000.0f / maxFPS - frameTicks);
		}

		return fps;
	}

	void FPSLimiter::CalculateFPS()
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

}