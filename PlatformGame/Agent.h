#pragma once

#include <glm\glm.hpp>
#include <ApocalypseEngine\GLTexture.h>
#include <ApocalypseEngine\SpriteBatch.h>
#include <ApocalypseEngine\ResourceManager.h>
#include <ApocalypseEngine\Rectangle.h>

class Friendly;
class Enemy;

class Agent
{
public:
	Agent();
	virtual ~Agent();

	void render(SpriteBatch& spriteBatch);

	virtual void update() = 0;

	inline glm::vec2 getPosition() const { return position_; }
	inline glm::vec2 getSize() const { return size_; }
	inline float getSpeed() const { return speed_; }
	inline float getDepth() const { return depth_; }
	inline GLTexture getTexture() const { return texture_; }

	inline void setPosition(glm::vec2& newPos) { position_ = newPos; }
	inline void setColor(GLuint r, GLuint g, GLuint b, GLuint a) { color_.r = r; color_.g = g; color_.b = b; color_.a = a; }

protected:
	glm::vec2 position_, size_;
	GLTexture texture_;
	float speed_, depth_;
	Color color_;
};

