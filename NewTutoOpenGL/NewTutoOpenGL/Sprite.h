#ifndef DEF_SPRITE
#define DEF_SPRITE

#include "glew.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init(float initX, float initY, float initWidth, float initHeight);

	void Draw();

private:
	float x;
	float y;
	float width;
	float height;
	GLuint vboID;
};

#endif