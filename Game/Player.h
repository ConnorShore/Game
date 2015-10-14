#pragma once

#include <ApocalypseEngine/Actor.h>

#include <glm/glm.hpp>

class Player : public Actor
{
public:
	Player(glm::vec3& position, CollisionType colType, float rotation = 0.0f, glm::vec3& rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f), float scale = 1.0f);
	~Player();

	void initPlayer();
	void update() override;

	float getWalkSpeed() const { return _walkSpeed; }

private:
	float _walkSpeed;
};