#ifndef DEF_VERTEX
#define DEF_VERTEX

#include "glew.h"

// a struct inside a struct is a composition

struct Position
{
	float x;
	float y;
};

struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct UV
{
	float u;
	float v;
};

struct Vertex
{
	// the x and y position
	Position position;

	// one byte(octet) per channel
	Color color;

	// uv texture coordinates
	UV uv;

	void SetPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void SetUV(float u, float v)
	{
		uv.u = u;
		uv.v = v;
	}
};

#endif
