#pragma once

#include "Entity.h"

class Entity;

enum ComponentType
{
	CMP_POSITION, CMP_VELOCITY, CMP_DRAW, CMP_INPUT
};

struct Component
{
	virtual void update() = 0;

	//Add serialization

	Entity* parent;
	ComponentType type;
};