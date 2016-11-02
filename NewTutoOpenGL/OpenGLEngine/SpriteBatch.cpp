#include "SpriteBatch.h"

namespace OpenGLEngine
{
	SpriteBatch::SpriteBatch() : 
		vbo(0), 
		vao(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::Init()
	{
		CreateVertexArray();
	}

	void SpriteBatch::Begin(GlyphSortType theSortType /* GlyphSortType::TEXTURE*/)
	{
		sortType = theSortType;
	}

	void SpriteBatch::End()
	{
		SortGlyphs();

	}

	void SpriteBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color)
	{
		Glyph* newGlyph = new Glyph();
		newGlyph->texture = texture;
		newGlyph->depth = depth;

		newGlyph->topLeft.color = color;
		newGlyph->topLeft.SetPosition(destRect.x, destRect.y + uvRect.w);
		newGlyph->topLeft.SetUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyph->bottomLeft.color = color;
		newGlyph->bottomLeft.SetPosition(destRect.x, destRect.y);
		newGlyph->bottomLeft.SetUV(uvRect.x, uvRect.y);

		newGlyph->topRight.color = color;
		newGlyph->topRight.SetPosition(destRect.x + destRect.z, destRect.y + uvRect.w);
		newGlyph->topRight.SetUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		newGlyph->bottomRight.color = color;
		newGlyph->bottomRight.SetPosition(destRect.x + destRect.z, destRect.y);
		newGlyph->bottomRight.SetUV(uvRect.x + uvRect.z, uvRect.y);

		glyphs.push_back(newGlyph);
	}

	void SpriteBatch::RenderBatch()
	{

	}

	void SpriteBatch::CreateVertexArray()
	{
		if (vao == 0)
		{
			glGenVertexArrays(1, &vao);
		}
		glBindVertexArray(vao);

		if (vbo == 0)
		{
			glGenBuffers(1, &vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		// attribute the index 0 to the buffer
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// this is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		// this is the color attribute pointer (normalized)
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		// this is the uv attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		// unbind the vao
		glBindVertexArray(0);
	}

	void SpriteBatch::SortGlyphs()
	{
		switch (sortType)
		{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(glyphs.begin(), glyphs.end(), CompareBackToFront);
			break;

		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(glyphs.begin(), glyphs.end(), CompareFrontToBack);
			break;

		case GlyphSortType::TEXTURE:
			std::stable_sort(glyphs.begin(), glyphs.end(), CompareTexture);
			break;
		}
	}

	bool SpriteBatch::CompareFrontToBack(Glyph* a, Glyph* b)
	{
		return (a->depth < b->depth);
	}

	bool SpriteBatch::CompareBackToFront(Glyph* a, Glyph* b)
	{
		return (a->depth > b->depth);
	}

	bool SpriteBatch::CompareTexture(Glyph* a, Glyph* b)
	{
		return (a->texture < b->texture);
	}

}