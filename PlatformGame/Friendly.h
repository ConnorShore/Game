#pragma once

#include "Agent.h"

class Friendly : public Agent
{
public:
	Friendly();
	virtual ~Friendly();

	virtual void update();
};

