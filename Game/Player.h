#pragma once

#include "Asset.h"

#include <glm/glm.hpp>

class Player : public Asset
{
public:
	Player(glm::vec3& position, float rotation = 0.0f, glm::vec3& rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f), float scale = 1.0f);
	~Player();

	void initPlayer();
	void update();

	glm::vec3 getDirection() const { return _direction; }
	float getWalkSpeed() const { return _walkSpeed; }

private:
	glm::vec3 _direction;
	float _walkSpeed = 5.0f;
};