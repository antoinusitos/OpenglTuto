#pragma once
#include <string>
#include <glm.hpp>
#include <vector>
#include "Bullet.h"

class Gun
{
public:
	Gun(std::string name, int fireRate, int bulletsPerShot, float spread, float bulletSpeed, int damage);
	~Gun();

	void Update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets);

private:

	void Fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet>& bullets);
	
	std::string _name;

	int _fireRate; /// frames => à changer

	int _bulletsPerShot;

	float _spread; /// accuracy

	float _bulletSpeed;

	int _bulletDamage;

	int _frameCounter;
};

