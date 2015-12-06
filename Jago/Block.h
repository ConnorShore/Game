#pragma once

#include "StaticBox.h"

#include <Box2D\Box2D.h>

#include <ApocalypseEngine\GLTexture.h>
#include <ApocalypseEngine\SpriteBatch.h>

class Block
{
public:
	Block();
	~Block();

	virtual void init(b2World* _world, const glm::vec2& position, GLTexture texture, float depth, bool collidable);
	virtual void update();
	virtual void render(SpriteBatch& spriteBatch);

	GLubyte getBrightness() { return _brightness; }
	StaticBox getStaticBox() { return _staticBox; }
	glm::vec2 getPosition() { return glm::vec2(_staticBox.getPosition().x, _staticBox.getPosition().y); }

	void setBrightness(GLubyte value) { _brightness = value; }

protected:
	StaticBox _staticBox;
	GLubyte _brightness;
	float _depth;
	const float _size = 1.0f;
	bool _collidable;
	GLTexture _texture;
};