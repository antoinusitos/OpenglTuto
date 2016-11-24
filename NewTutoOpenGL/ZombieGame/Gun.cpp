#include "Gun.h"
#include <random>
#include <ctime>
#include <gtx/rotate_vector.hpp>


Gun::Gun(std::string name, int fireRate, int bulletsPerShot, float spread, float bulletSpeed, int damage)
{
	_name = name;
	_fireRate = fireRate;
	_bulletsPerShot = bulletsPerShot;
	_spread = spread;
	_bulletSpeed = bulletSpeed;
	_bulletDamage = _bulletDamage;
	_frameCounter = 0;
}


Gun::~Gun()
{
}

void Gun::Update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets)
{
	_frameCounter++;
	if (_frameCounter >= _fireRate && isMouseDown)
	{
		Fire(direction, position, bullets);
		_frameCounter = 0;
	}
}

void Gun::Fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet>& bullets)
{
	static std::mt19937 randomEngine(time(nullptr));

	static std::uniform_real_distribution<float> randRotate(-_spread, _spread);

	for (int i = 0; i < _bulletsPerShot; ++i)
	{
		bullets.emplace_back(position, glm::rotate(direction, randRotate(randomEngine)), _bulletDamage, _bulletSpeed);
	}
}
