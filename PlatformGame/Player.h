#pragma once

#include <ApocalypseEngine\InputManager.h>
#include "Friendly.h"

class Player : public Friendly
{
public:
	Player();
	~Player();

	void init(glm::vec2& position);
	void input(InputManager& input);
	void update() override;

private:

};

