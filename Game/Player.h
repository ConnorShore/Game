#pragma once

#include "Asset.h"
#include "InputManager.h"

class Player : public Asset
{
public:
	Player(glm::vec3& position);
	~Player();

	void input(InputManager& inputManager);
	void update();

private:
	float _speed = 0.25f;
};
