#ifndef DEF_TIMING
#define DEF_TIMING

namespace OpenGLEngine
{
	class FPSLimiter
	{
	public:
		FPSLimiter();
		~FPSLimiter();

		void Init(float theTargetFPS);

		void SetMaxFPS(float theTargetFPS);

		// get the current Time
		void Begin();

		// calculate the fps, limit it and return the fps
		float End();

	private:
		void CalculateFPS();

		float maxFPS;
		unsigned int startTicks;
		float fps;
		float frameTime;
	};
}

#endif