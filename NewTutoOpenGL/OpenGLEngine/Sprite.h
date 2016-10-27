#ifndef DEF_SPRITE
#define DEF_SPRITE

#include "glew.h"
#include "GLTexture.h"

#include <string>

namespace OpenGLEngine
{

	using namespace std;

	// a 2D quad
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void Init(float initX, float initY, float initWidth, float initHeight, string path);

		void Draw();

	private:
		float x;
		float y;
		float width;
		float height;
		GLuint vboID;
		GLTexture texture;
	};

}

#endif