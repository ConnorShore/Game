#include "Collision.h"

#include <algorithm>
#include <glm\glm.hpp>


Collision::Collision()
{
}

bool Collision::checkAABBCollision(Rectangle r1, Rectangle r2)
{
	float aLeft = r1.getPosition().x;
	float aRight = aLeft + r1.getDimension().x;
	float aBottom = r1.getPosition().y;
	float aTop = aBottom + r1.getDimension().y;

	float bLeft = r2.getPosition().x;
	float bRight = bLeft + r2.getDimension().x;
	float bBottom = r2.getPosition().y;
	float bTop = bBottom + r2.getDimension().y;

	return checkOverlapping(aLeft, aRight, bLeft, bRight) && checkOverlapping(aBottom, aTop, bBottom, bTop);
}

void Collision::actAABBCollision(Actor* actor1, Actor* actor2)
{
	const float ACTOR1_SIZE_X = actor1->getBounds().getDimension().x / 2.0f;
	const float ACTOR1_SIZE_Y = actor1->getBounds().getDimension().y / 2.0f;
	const float ACTOR2_SIZE_X = actor2->getBounds().getDimension().x / 2.0f;
	const float ACTOR2_SIZE_Y = actor2->getBounds().getDimension().y / 2.0f;

	const float MIN_DIST_X = ACTOR1_SIZE_X + ACTOR2_SIZE_X;
	const float MIN_DIST_Y = ACTOR1_SIZE_Y + ACTOR2_SIZE_Y;

	glm::vec3 distVec = actor1->getPosition() - actor2->getPosition();

	float xDepth = MIN_DIST_X - glm::abs(distVec.x);
	float yDepth = MIN_DIST_Y - glm::abs(distVec.y);

	if (xDepth > 0 && yDepth > 0) {
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
			if (distVec.x < 0) {
				actor1->setPosition(glm::vec3(actor1->getPosition().x - xDepth, actor1->getPosition().y, actor1->getPosition().z));
			}
			else {
				actor1->setPosition(glm::vec3(actor1->getPosition().x + xDepth, actor1->getPosition().y, actor1->getPosition().z));
			}
		}
		else {
			if (distVec.y < 0) {
				actor1->setPosition(glm::vec3(actor1->getPosition().x, actor1->getPosition().y - yDepth, actor1->getPosition().z));
			}
			else {
				actor1->setPosition(glm::vec3(actor1->getPosition().x, actor1->getPosition().y + yDepth, actor1->getPosition().z));
			}
		}
	}
}

bool Collision::checkOverlapping(float minA, float maxA, float minB, float maxB)
{
	return minB <= maxA && minA <= maxB;
}

Collision::~Collision()
{
}
