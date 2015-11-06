#pragma once

#include "Actor.h"
#include "Rectangle.h"
#include "Circle.h"

class Collision
{
public:
	Collision();
	~Collision();

	static bool checkAABBCollision(Rectangle r1, Rectangle r2);
	static void actAABBCollision(Actor* actor1, Actor* actor2);

private:
	static bool checkOverlapping(float minA, float maxA, float minB, float maxB);
};

