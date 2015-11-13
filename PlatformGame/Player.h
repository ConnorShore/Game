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
	void update(const std::vector<std::string>& levelData, std::vector<Friendly*>& friends, std::vector<Enemy*>& enemies) override;

private:

};

