#pragma once

#include "Light.h"

#include <glm\glm.hpp>
#include <ApocalypseEngine\Vertex2D.h>
#include <ApocalypseEngine\GLTexture.h>

class Torch : public Light
{
public:
	Torch();
	~Torch();

	void init(const glm::vec2& position, float size, Color color) override;
	void update() override;
	void render(SpriteBatch& spriteBatch) override;
	
	glm::vec2 getPosition() { return _position; }
	GLTexture getTexture() const { return _texture; }
	Light2D getLight() const { return _light; }

private:
	GLTexture _texture;

	glm::vec2 _dimension;

	float _count = 0.0f;
};

