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

void Light::update()
{
	if (_flicker) {
		static float initSize = _light.size;
		static GLubyte initPow = _light.color.a;

		_light.size = initSize + (glm::cos(_count) / 2.5f);
		_count += 0.05f;
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
