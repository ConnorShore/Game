#pragma once

#include "Agent.h"

class Friendly : public Agent
{
public:
	Friendly();
	virtual ~Friendly();

	virtual void update(const std::vector<std::string>& levelData, std::vector<Friendly*>& friends, std::vector<Enemy*>& enemies) override;
};

