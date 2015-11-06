#pragma once

#include <vector>

#include "Actor.h"
#include "Rectangle.h"

class PhysicsCore
{
public:
	PhysicsCore();
	~PhysicsCore();

	void updateCollision(std::vector<Actor*>& actor);

private:

};