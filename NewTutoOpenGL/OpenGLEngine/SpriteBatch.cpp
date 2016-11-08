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
		renderBatches.clear();
		for (int i = 0; i < glyphs.size(); ++i)
		{
			delete glyphs[i];
		}

		glyphs.clear();
	}

	void SpriteBatch::End()
	{
		SortGlyphs();
		CreateRenderBatches();
	}

	void SpriteBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color)
	{
		Glyph* newGlyph = new Glyph();
		newGlyph->texture = texture;
		newGlyph->depth = depth;

		newGlyph->topLeft.color = color;
		newGlyph->topLeft.SetPosition(destRect.x, destRect.y + destRect.w);
		newGlyph->topLeft.SetUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyph->bottomLeft.color = color;
		newGlyph->bottomLeft.SetPosition(destRect.x, destRect.y);
		newGlyph->bottomLeft.SetUV(uvRect.x, uvRect.y);

		newGlyph->topRight.color = color;
		newGlyph->topRight.SetPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		newGlyph->topRight.SetUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		newGlyph->bottomRight.color = color;
		newGlyph->bottomRight.SetPosition(destRect.x + destRect.z, destRect.y);
		newGlyph->bottomRight.SetUV(uvRect.x + uvRect.z, uvRect.y);

		glyphs.push_back(newGlyph);
	}

	void SpriteBatch::RenderBatch()
	{
		glBindVertexArray(vao);

		for (int i = 0; i < renderBatches.size(); ++i)
		{
			glBindTexture(GL_TEXTURE_2D, renderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].numVertices);
		}
		glBindVertexArray(0);
	}

	void SpriteBatch::CreateRenderBatches()
	{
		std::vector<Vertex> vertices;
		// allocate the memory of the vector to speed up the program
		// we don't have to use push_back, use [] instead
		vertices.resize(glyphs.size() * 6);

		if (glyphs.empty()) return;

		int offset = 0;
		int currentVertex = 0;
		// Commented because of the use of emplace_back
		//RenderBatch myBatch(0, 6, glyphs[0]->texture);
		renderBatches.emplace_back(offset, 6, glyphs[0]->texture);

		vertices[currentVertex] = glyphs[0]->topLeft;
		currentVertex++;
		vertices[currentVertex] = glyphs[0]->bottomLeft;
		currentVertex++;
		vertices[currentVertex] = glyphs[0]->bottomRight;
		currentVertex++;
		vertices[currentVertex] = glyphs[0]->bottomRight;
		currentVertex++;
		vertices[currentVertex] = glyphs[0]->topRight;
		currentVertex++;
		vertices[currentVertex] = glyphs[0]->topLeft;
		currentVertex++;

		offset += 6;

		for (int currentGlyph = 1; currentGlyph < glyphs.size(); ++currentGlyph)
		{
			// create a new render batch because we have a new texture
			if (glyphs[currentGlyph]->texture != glyphs[currentGlyph - 1]->texture)
				renderBatches.emplace_back(offset, 6, glyphs[currentGlyph]->texture);
			else
				renderBatches.back().numVertices += 6;

			vertices[currentVertex] = glyphs[currentGlyph]->topLeft;
			currentVertex++;
			vertices[currentVertex] = glyphs[currentGlyph]->bottomLeft;
			currentVertex++;
			vertices[currentVertex] = glyphs[currentGlyph]->bottomRight;
			currentVertex++;
			vertices[currentVertex] = glyphs[currentGlyph]->bottomRight;
			currentVertex++;
			vertices[currentVertex] = glyphs[currentGlyph]->topRight;
			currentVertex++;
			vertices[currentVertex] = glyphs[currentGlyph]->topLeft;
			currentVertex++;
			offset += 6;
		}

		// create a vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		// orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		// upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		// free the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
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