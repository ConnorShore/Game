#pragma once

#include <GL/glew.h>
#include <string>

struct GLTexture
{
	GLuint id;
	int width, height;
	std::string filePath;
};