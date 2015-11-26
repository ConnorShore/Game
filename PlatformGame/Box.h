#pragma once

#include <glm/glm.hpp>
#include <Box2D/Box2D.h>

class Box
{
public:
	Box();
	~Box();

	void init(b2World* world, const glm::vec2& position, const glm::vec2& dimension);

	b2Body* getBody() const { return _body; }
	b2Fixture* getFixture() const { return _fixture; }
	const glm::vec2& getDimension() const { return _dimension; }

private:
	b2Body* _body = nullptr;
	b2Fixture* _fixture = nullptr;
	glm::vec2 _dimension;
};

