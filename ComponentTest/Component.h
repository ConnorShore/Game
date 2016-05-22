#pragma once

#include "Entity.h"

#include <string>

class Entity;

struct Component
{
	virtual void update() = 0;
	virtual void serialize(/*Reader*/) = 0;
	virtual void deserialize(/*Reader*/) = 0;

	Entity* parent;
	std::string name;
};