#pragma once

#include "Entity.h"

#include <string>

class Entity;

struct Component
{
	virtual void update() = 0;
	virtual void serialize() = 0;
	virtual void deserialize() = 0;

	Entity* parent = nullptr;
	std::string name = "Default";
};