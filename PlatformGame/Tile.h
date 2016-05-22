#pragma once

#include <glm/glm.hpp>
#include <Box2D/Box2D.h>
#include <ApocalypseEngine\GLTexture.h>
#include <ApocalypseEngine\SpriteBatch.h>

class Tile
{
public:
	Tile();
	~Tile();

	void init(b2World* world, const glm::vec2& position, const glm::vec2& dimension, GLTexture texture, glm::vec4 uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	void init(b2World* world, const glm::vec2& position, const glm::vec2& dimension);
	void render(SpriteBatch& spriteBatch);

	b2Body* getBody() const { return _body; }
	b2Fixture* getFixture() const { return _fixture; }
	const glm::vec2& getDimension() const { return _dimension; }

private:
	b2Body* _body = nullptr;
	b2Fixture* _fixture = nullptr;
	glm::vec2 _dimension;
	glm::vec4 _uvRect;
	GLTexture _texture;
};

