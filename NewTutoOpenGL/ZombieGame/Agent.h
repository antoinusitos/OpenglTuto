#pragma once

#include <glm.hpp>
#include <OpenGLEngine/SpriteBatch.h>

const float AGENT_WIDTH = 60;

class Agent
{
public:
	Agent();
	virtual ~Agent();

	virtual void Update() = 0;

	void Draw(OpenGLEngine::SpriteBatch& spriteBatch);

	glm::vec2 GetPosition() const { return _position; }

protected:
	glm::vec2 _position;
	OpenGLEngine::Color _color;
	float _speed;
};

