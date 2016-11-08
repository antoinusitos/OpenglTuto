#ifndef DEF_BULLET
#define DEF_BULLET

#include <glm.hpp>
#include <SpriteBatch.h>

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Init(glm::vec2 pos, glm::vec2 dir, float s, int theLifeTime);
	void Draw(OpenGLEngine::SpriteBatch& spriteBatch);
	
	// return true when this must be destroyed
	bool Update();

private:
	int lifeTime;
	float speed;
	glm::vec2 direction;
	glm::vec2 position;
};

#endif