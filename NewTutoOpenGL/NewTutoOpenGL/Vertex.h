#ifndef DEF_VERTEX
#define DEF_VERTEX

#include "glew.h"

// a struct inside a struct is a composition

struct Position
{
	float x;
	float y;
}

struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
}

struct Vertex
{
	// the x and y position
	Position position;

	// one byte(octet) per channel
	Color color;
};

#endif
