#pragma once

#include "Block.h"
#include "Player.h"

#include <glm\glm.hpp>

#include <ApocalypseEngine\Vertex2D.h>
#include <ApocalypseEngine\GLTexture.h>
#include <ApocalypseEngine\Light2D.h>
#include <ApocalypseEngine\SpriteBatch.h>

class Light
{
public:
	Light();
	~Light();

	virtual void initObj(const glm::vec2& position, const glm::vec2& dimension, float size, Color color, GLTexture texture, bool flicker = false);
	virtual void initRawLight(const glm::vec2& position, float size, Color color, bool flicker = false);
	virtual void update(Player& player, std::vector<Block>& blocks);
	virtual void render(SpriteBatch& spriteBatch);
	virtual void renderRawLight(SpriteBatch& spriteBatch);
	
	glm::vec2 getPosition() { return _position; }
	const glm::vec2& getDimension() const { return _dimension; }
	GLTexture getTexture() const { return _texture; }
	Light2D getLight() const { return _light; }

protected:
	Light2D _light;
	GLTexture _texture;
	glm::vec2 _position, _dimension;
	bool _flicker = false;
	float _count = 0.0f;
	float _depth = 1.0f;
};

