#pragma once

#include "Vertex2D.h"
#include "SpriteBatch.h"

#include <glm\glm.hpp>

class Light2D
{
public:
	virtual void render(SpriteBatch& spriteBatch) {
		glm::vec4 destRect;
		destRect.x = position.x - size / 2.0f;
		destRect.y = position.y - size / 2.0f;
		destRect.z = size;
		destRect.w = size;
		spriteBatch.addToBatch(destRect, glm::vec4(-1.0f, -1.0f, 2.0f, 2.0f), 0.0f, 0, color, 0.0f);
	}

	Color color;
	glm::vec2 position;
	float size;
};

