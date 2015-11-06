#pragma once

#include "Asset.h"
#include "Rectangle.h"

enum class CollisionType {RECTANGLE, CIRCLE};

class Actor : public Asset
{
public:
	Actor(glm::vec3& position, CollisionType colType, float rotation = 0.0f, glm::vec3& rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f), float scale = 1.0f);
	~Actor();

	Rectangle createRectangleBoundsToModel();
	Rectangle createRectangleBounds(float x, float y, float width, float height);
	bool addBounds(Rectangle& rect, bool centered);

	void update() override;

	void setBounds(Rectangle& newBounds) { bounds_ = newBounds; }

	Rectangle getBounds() const { return bounds_; }
	CollisionType getCollisionType() const { return collisionType_; }

protected:
	CollisionType collisionType_;
	Rectangle bounds_;
};

