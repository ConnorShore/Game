#pragma once

#include "GLTexture.h"

#include <glm/glm.hpp>
#include <GL\glew.h>
#include <string>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height, const std::string& texturePath);
	void render();

private:
	float _x, _y, _width, _height;
	GLuint _vboID;
	GLTexture _texture;
};

