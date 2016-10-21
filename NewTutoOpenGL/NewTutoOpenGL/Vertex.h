#ifndef DEF_VERTEX
#define DEF_VERTEX

#include "glew.h"

// a struct inside a struct is a composition

struct Vertex
{
	// the x and y position
	struct Position
	{
		float x;
		float y;
	} position;
	// one byte(octet) per channel
	struct Color
	{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	} color;
};

#endif
