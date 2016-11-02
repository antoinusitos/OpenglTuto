#ifndef DEF_SPRITEBATCH
#define DEF_SPRITEBATCH

#include <glew.h>
#include <glm.hpp>
#include <vector>
#include "Vertex.h"
#include <algorithm>

namespace OpenGLEngine
{

	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE,
	};

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

	// used to load once each texture
	class RenderBatch
	{
	public :
		RenderBatch(GLuint theOffset, GLuint theNumVertices, GLuint theTexture)
		{
			offset = theOffset;
			numVertices = theNumVertices;
			texture = theTexture;
		}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		// init the batch
		void Init();

		// set everything up and set ready for drawing 
		void Begin(GlyphSortType theSortType = GlyphSortType::TEXTURE);
		// set post-precessing stuff (sort, etc.)
		void End();

		// add all sprite we want to draw in this batch
		void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);
		// render this batch on the screen
		void RenderBatch();

	private:
		void CreateRenderBatches();
		void CreateVertexArray();

		void SortGlyphs();

		static bool CompareFrontToBack(Glyph* a, Glyph* b);
		static bool CompareBackToFront(Glyph* a, Glyph* b);
		static bool CompareTexture(Glyph* a, Glyph* b);

		GLuint vbo;
		GLuint vao;

		GlyphSortType sortType;

		std::vector<Glyph*> glyphs;
		
		std::vector<OpenGLEngine::RenderBatch> renderBatches;
	};
}

#endif