#ifndef DEF_SPRITEBATCH
#define DEF_SPRITEBATCH

#include <glew.h>
#include "Vertex.h"

namespace OpenGLEngine
{
	// just a single sprite (all the infos)
	struct Glyph
	{
		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		// init the batch
		void Init();

		// set everything up and set ready for drawing 
		void Begin();
		// set post-precessing stuff (sort, etc.)
		void End();

		// add all sprite we want to draw in this batch
		void Draw();
		// render this batch on the screen
		void RenderBatch();

	private:
		GLuint vbo;
		GLuint vao;
	};
}

#endif