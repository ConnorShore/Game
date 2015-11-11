#pragma once

#include <string>
#include <glm\glm.hpp>
#include <ApocalypseEngine\SpriteBatch.h>
#include <ApocalypseEngine\GLTexture.h>

class Bullet
{
public:
	Bullet(glm::vec2 position, glm::vec2 direction, float speed, const std::string& texturePath);
	~Bullet();

	void update();
	void render(SpriteBatch& spriteBatch);

private:
	glm::vec2 _position, _direction;
	float _speed;
	GLTexture _texture;
	const float _size = 10.0f;
};