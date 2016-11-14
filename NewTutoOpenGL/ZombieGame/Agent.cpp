#include "Agent.h"
#include <OpenGLEngine/ResourceManager.h>


Agent::Agent()
{
}


Agent::~Agent()
{
}

void Agent::Draw(OpenGLEngine::SpriteBatch& spriteBatch)
{
	static int textureID = OpenGLEngine::ResourceManager::GetTexture("Textures/circle.png").id;

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	spriteBatch.Draw(destRect, uvRect, textureID, 0.0f, _color);
}
