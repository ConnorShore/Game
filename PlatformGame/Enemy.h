#pragma once

#include "Agent.h"

class Enemy : public Agent
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void update() override;
};

