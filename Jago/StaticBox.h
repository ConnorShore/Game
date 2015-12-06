#pragma once

#include <Box2D\Box2D.h>
#include <glm\glm.hpp>

#include <ApocalypseEngine\GLTexture.h>
#include <ApocalypseEngine\SpriteBatch.h>

class StaticBox
{
public:
	StaticBox();
	~StaticBox();

	void init(b2World* world, const glm::vec2& position, const glm::vec2& dimension, GLTexture texture, bool lightAffected = true, bool collidable = false);
	void init(b2World* world, const glm::vec2& position, const glm::vec2& dimension);

	void update();

	void render(SpriteBatch& spriteBatch);

	b2Body* getBody() const { return _body; }
	glm::vec2 getPosition() { return _position; }
	const glm::vec2& getDimension() const { return _dimension; }
	bool isLightAffected() const { return _lightAffected; }
	GLTexture getTexture() const { return _texture; }

private:
	b2Body* _body;
	glm::vec2 _position, _dimension;
	GLTexture _texture;
	float _brightness;
	bool _lightAffected, _collidable;
};

