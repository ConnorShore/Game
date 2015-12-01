#pragma once

#include <Box2D\Box2D.h>
#include <glm\glm.hpp>

#include <ApocalypseEngine\SpriteBatch.h>
#include <ApocalypseEngine\GLTexture.h>

class Box
{
public:
	Box();
	~Box();

	void init(b2World* world, const glm::vec2& position, const glm::vec2& dimension, GLTexture texture, bool fixedRotation, const glm::vec4& uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	void render(SpriteBatch& spriteBatch);

	b2Body* getBody() const { return _body; }
	b2Fixture* getFixture() const { return _fixture; }
	const glm::vec2& getDimension() const { return _dimension; }

private:
	b2Body* _body = nullptr;
	b2Fixture* _fixture = nullptr;

	GLTexture _texture;

	glm::vec2 _dimension;
	glm::vec4 _uvRect;
};

