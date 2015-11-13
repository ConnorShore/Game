#pragma once

#include "Agent.h"

class Enemy : public Agent
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void update(const std::vector<std::string>& levelData, std::vector<Friendly*>& friends, std::vector<Enemy*>& enemies) override;
};

