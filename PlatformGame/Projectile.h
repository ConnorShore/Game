#pragma once

#include <string>
#include <glm/glm.hpp>
#include <ApocalypseEngine\GLTexture.h>
#include <ApocalypseEngine\SpriteBatch.h>
#include <Box2D\Box2D.h>

class Projectile
{
public:
	Projectile(b2World* world, const glm::vec2& position, const glm::vec2& direction, float speed, const std::string& texturePath, float size = 1.0f, bool gravity = false);
	~Projectile();
	
	virtual void update() = 0;
	virtual void render(SpriteBatch& spriteBatch) = 0;

	virtual inline b2Body* getBody() { return body_; }
	virtual inline b2Fixture* getFixture() { return fixture_; }

	virtual inline const glm::vec2& getPosition() { return position_; }
	virtual inline const glm::vec2& getDirection() { return direction_; }
	virtual inline float getSize() { return size_; }
	virtual inline float getSpeed() { return speed_; }
	virtual inline GLTexture getTexture() { return texture_; }
	virtual inline bool hasGravity() { return gravity_; }

protected:
	b2Body* body_ = nullptr;
	b2Fixture* fixture_ = nullptr;

	glm::vec2 position_, direction_;
	float size_, speed_;
	GLTexture texture_;
	bool gravity_;
};

