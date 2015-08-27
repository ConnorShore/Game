#pragma once

#include "Camera.h"

#include <glm/glm.hpp>

class Player
{
public:
	Player();
	~Player();

	void init(Camera camera);
	void update(Camera camera);

	glm::vec3 getPosition() const { return _position; }

private:
	glm::vec3 _position;
};

