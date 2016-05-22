#pragma once

#include <glm\glm.hpp>
#include <ApocalypseEngine\GLTexture.h>
#include <ApocalypseEngine\Vertex2D.h>

struct Tile {
	GLTexture texture;
	glm::vec2 position;
	GLubyte brightness;
	bool isCollidable;
	float depth;

	void init(glm::vec2 pos, GLTexture tex, float dep, bool collide) {
		position = pos;
		texture = tex;
		isCollidable = collide;
		brightness = 10;
		depth = dep;
	}

	void render(SpriteBatch& spriteBatch) {
		glm::vec4 destRect;
		destRect.x = position.x;
		destRect.y = position.y;
		destRect.z = 1.0f;
		destRect.w = 1.0f;
		spriteBatch.addToBatch(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), depth, texture.id, Color(brightness, brightness, brightness, 255));
	}
};