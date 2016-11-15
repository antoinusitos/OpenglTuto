#pragma once
#include "Agent.h"

class Zombie : public Agent
{
public:
	Zombie();
	~Zombie();

	virtual void Update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& Zombies);
};

