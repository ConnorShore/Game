#pragma once

#include <ApocalypseEngine\Light2D.h>

class Light
{
public:
	Light();
	~Light();

	virtual void init(const glm::vec2& position, float size, Color color) = 0;
	virtual void update() = 0;
	virtual void render(SpriteBatch& spriteBatch) = 0;

	glm::vec2 getPosition() { return _position; }
	float getSize() { return _size; }
	Color getColor() const { return _color; }
	const Light2D getLight() const { return _light; }

protected:
	glm::vec2 _position;
	float _size;
	Color _color;
	Light2D _light;
};

