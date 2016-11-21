#include "Zombie.h"
#include "Human.h"


Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}

void Zombie::Init(float speed, glm::vec2 pos)
{
	_speed = speed;
	_position = pos;
	_color.r = 0;
	_color.g = 160;
	_color.b = 0;
	_color.a = 255;
}

void Zombie::Update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& Zombies)
{

	Human* closestHuman = GetNearestHuman(humans);

	if(closestHuman != nullptr)
	{
		glm::vec2 direction = glm::normalize(closestHuman->GetPosition() - _position);
		_position += direction * _speed;
	}

	if (CollideWithLevel(levelData))
	{

	}
}

Human* Zombie::GetNearestHuman(std::vector<Human*>& humans)
{
	Human* closestHuman = nullptr;
	float smallestDistance = 9999999.0f;

	for (int i = 0; i < humans.size(); ++i)
	{
		glm::vec2 distVec = humans[i]->GetPosition() - _position;
		float distance = glm::length(distVec);

		if(distance < smallestDistance)
		{
			smallestDistance = distance;
			closestHuman = humans[i];
		}
	}
	
	return closestHuman;
}
