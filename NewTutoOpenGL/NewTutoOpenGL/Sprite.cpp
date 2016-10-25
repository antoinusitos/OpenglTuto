#include "Sprite.h"
#include "Vertex.h"

#include <cstddef>

Sprite::Sprite()
{
	vboID = 0;
}


Sprite::~Sprite()
{
	if (vboID != 0)
	{
		glDeleteBuffers(1, &vboID);
	}
}

void Sprite::Init(float initX, float initY, float initWidth, float initHeight)
{
	x = initX;
	y = initY;
	width = initWidth;
	height = initHeight;

	// convert the coordinates from plan (-1,1) to screen (0,1)

	// if VBO is not initiliazed, create one
	if (vboID == 0)
	{
		glGenBuffers(1, &vboID);
	}

	// 6 vertices
	Vertex vertexData[6];

	// first triangle
	vertexData[0].SetPosition(x + width, y + height);
	vertexData[0].SetUV(1.0f, 1.0f);

	vertexData[1].SetPosition(x, y + height);
	vertexData[1].SetUV(0.0f, 1.0f);

	vertexData[2].SetPosition(x, y);
	vertexData[2].SetUV(0.0f, 0.0f);

	//second triangle
	vertexData[3].SetPosition(x, y);
	vertexData[3].SetUV(0.0f, 0.0f);

	vertexData[4].SetPosition(x + width, y);
	vertexData[4].SetUV(1.0f, 0.0f);

	vertexData[5].SetPosition(x + width, y + height);
	vertexData[5].SetUV(1.0f, 1.0f);

	for (int i = 0; i < 6; ++i)
	{
		vertexData[4].SetColor(255, 0, 255, 255);
	}

	vertexData[1].SetColor(0, 0, 255, 255);

	vertexData[4].SetColor(0, 255, 0, 255);

	// init a buffer for the vbo
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// upload the vertex data in the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	// clear the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Draw()
{
	// declare a buffer for the vbo
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

		// attribute the index 0 to the buffer
		glEnableVertexAttribArray(0);

			// this is the position attribute pointer
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
			// this is the color attribute pointer (normalized)
			glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
			// this is the uv attribute pointer
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

			// Draw 6 vertices
			glDrawArrays(GL_TRIANGLES, 0, 6);

		// disable the buffer
		glDisableVertexAttribArray(0);

	// unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
