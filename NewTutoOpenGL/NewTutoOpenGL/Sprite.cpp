#include "Sprite.h"

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

	// 6 vertices * xy
	float vertexData[6 * 2];

	// first triangle
	vertexData[0] = x + width;
	vertexData[1] = y + height;

	vertexData[2] = x ;
	vertexData[3] = y + height;

	vertexData[4] = x;
	vertexData[5] = y;

	//second triangle
	vertexData[6] = x;
	vertexData[7] = y;

	vertexData[8] = x + width;
	vertexData[9] = y;

	vertexData[10] = x + width;
	vertexData[11] = y + height;

	// init a buffer for the vbo
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// put the vertex data in the buffer
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

			// tell opengl to draw two float for each vertices
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

			// Draw 6 vertices
			glDrawArrays(GL_TRIANGLES, 0, 6);

		// disable the buffer
		glDisableVertexAttribArray(0);

	// unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
