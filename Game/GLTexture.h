#pragma once

#include <GL/glew.h>

struct GLTexture
{
	GLuint id;
	int width, height;

	float shineLevel, shineDamp;

	float getShineLevel() const { return shineLevel; }
	float getShineDamp() const { return shineDamp; }

	void setShineLevel(float level) { shineLevel = level; }
	void setShineDamp(float damp) { shineDamp = damp; }
};