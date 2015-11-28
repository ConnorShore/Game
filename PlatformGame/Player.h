#pragma once

#include "Box.h"

#include <ApocalypseEngine\InputManager.h>

class Player
{
public:
	Player();
	~Player();

	void init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimension);

	void update(InputManager inputManager);
	void render(SpriteBatch& spriteBatch);

	const Box& getBox() const { return _collisionBox; }

private:
	Box _collisionBox;
};