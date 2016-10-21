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
	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;

	vertexData[1].position.x = x ;
	vertexData[1].position.y = y + height;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	//second triangle
	vertexData[3].position.x = x;
	vertexData[3].position.y = y;

	vertexData[4].position.x = x + width;
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;

	for (int i = 0; i < 6; ++i)
	{
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}

	vertexData[1].color.r = 0;
	vertexData[1].color.g = 0;
	vertexData[1].color.b = 255;
	vertexData[1].color.a = 255;

	vertexData[4].color.r = 0;
	vertexData[4].color.g = 255;
	vertexData[4].color.b = 0;
	vertexData[4].color.a = 255;

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

			// Draw 6 vertices
			glDrawArrays(GL_TRIANGLES, 0, 6);

		// disable the buffer
		glDisableVertexAttribArray(0);

	// unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
