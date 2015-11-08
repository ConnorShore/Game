#pragma once

#include <glm\glm.hpp>
#include <ApocalypseEngine\Sprite.h>

class Bullet : public Sprite
{
public:
	Bullet();
	~Bullet();

	void update();

private:
	glm::vec2 _position, _direction;
};

