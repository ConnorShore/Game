#include "Light.h"

#include <ApocalypseEngine\ResourceManager.h>

Light::Light()
{
}

Light::~Light()
{
}

void Light::initObj(const glm::vec2& position, const glm::vec2& dimension, float size, Color color, GLTexture texture, bool flicker /*false*/)
{
	_position = position;
	_dimension = dimension;
	_texture = texture;
	_flicker = flicker;

	_light.color = color;
	_light.size = size;

	_light.position = glm::vec2(_position.x, _position.y + _dimension.y);
}

void Light::initRawLight(const glm::vec2 & position, float size, Color color, bool flicker /*false*/)
{
	_light.position = position;
	_flicker = flicker;

	_light.color = color;
	_light.size = size;

	_light.position = glm::vec2(_position.x, _position.y + _dimension.y);
}

void Light::update(Player& player, std::vector<Block>& blocks)
{
	if (_flicker) {
		static float initSize = _light.size;
		static GLubyte initPow = _light.color.a;

		_light.size = initSize + (glm::cos(_count) / 2.5f);
		_count += 0.05f;
	}

	{
		glm::vec2 distance = glm::vec2(glm::abs(player.getPosition().x - getPosition().x), glm::abs(player.getPosition().y - getPosition().y));

		printf("%f\n", distance.x);

		if (distance.x > 5 || distance.y > 5) {
			player.setBrightness(5);
		}
		else if (distance.x > 4 || distance.y > 4) {
			player.setBrightness(35);
		}
		else if (distance.x > 3 || distance.y > 3) {
			player.setBrightness(80);
		}
		else if (distance.x > 2 || distance.y > 2) {
			player.setBrightness(140);
		}
		else if (distance.x > 1 || distance.y > 1) {
			player.setBrightness(200);
		}
		else {
			player.setBrightness(255);
		}
	}

	//Calculate color of blocks
	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i].getStaticBox().isLightAffected()) {
			glm::vec2 distance = glm::vec2(glm::abs(blocks[i].getPosition().x - getPosition().x), glm::abs(blocks[i].getPosition().y - getPosition().y));

			if (distance.x > 5 || distance.y > 5) {
				blocks[i].setBrightness(5);
			}
			else if (distance.x > 4 || distance.y > 4) {
				blocks[i].setBrightness(35);
			}
			else if (distance.x > 3 || distance.y > 3) {
				blocks[i].setBrightness(80);
			}
			else if (distance.x > 2 || distance.y > 2) {
				blocks[i].setBrightness(140);
			}
			else if (distance.x > 1 || distance.y > 1) {
				blocks[i].setBrightness(200);
			}
			else {
				blocks[i].setBrightness(255);
			}
		}
	}
}

void Light::render(SpriteBatch& spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = _position.x - _dimension.x / 2.0f;
	destRect.y = _position.y;
	destRect.z = _dimension.x;
	destRect.w = _dimension.y;

	spriteBatch.addToBatch(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), _depth, _texture.id, _light.color);
}

void Light::renderRawLight(SpriteBatch & spriteBatch)
{
	_light.render(spriteBatch);
}
