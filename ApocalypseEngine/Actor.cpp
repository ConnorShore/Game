#include "Actor.h"



Actor::Actor(glm::vec3& position, CollisionType colType, float rotation /*0.0f*/, glm::vec3& rotationAxis /*glm::vec3(0.0f,1.0f,0.0f)*/, float scale /*1.0f*/)
	: Asset(position, rotation, rotationAxis, scale), collisionType_(colType)
{
}

Rectangle Actor::createRectangleBoundsToModel()
{
	std::vector<glm::vec3> verts = getModel().getVertices();

	float minX = verts[0].x;
	float maxX = verts[0].x;
	float minY = verts[0].y;
	float maxY = verts[0].y;

	for (int i = 0; i < verts.size(); i++) {
		if (verts[i].x < minX) minX = verts[i].x;
		if (verts[i].x > maxX) maxX = verts[i].x;
		if (verts[i].y < minY) minY = verts[i].y;
		if (verts[i].y > maxY) maxY = verts[i].y;
	}

	Rectangle rect(glm::vec3(getPosition().x + minX, getPosition().y + minY, getPosition().z), glm::vec3(scale_ * (maxX - minX), scale_ * (maxY - minY), 0.0f));

	return rect;
}

Rectangle Actor::createRectangleBounds(float x, float y, float width, float height)
{
	Rectangle rect;
	rect.getPosition() = glm::vec3(x, y, getPosition().z);
	rect.getDimension() = glm::vec3(width, height, 0.0f);
	return rect;
}

bool Actor::addBounds(Rectangle& rect, bool centered)
{
	collisionType_ = CollisionType::RECTANGLE;

	if (centered) {
		rect.setPosition(getPosition());
		return true;
	}
	else {
		rect.setPosition(glm::vec3(getPosition().x - rect.getDimension().x / 2.0f, getPosition().y - rect.getDimension().y / 2.0f, getPosition().z));
		return true;
	}

	return false;
}

void Actor::update()
{
	bounds_.setPosition(getPosition());
}

Actor::~Actor()
{
}