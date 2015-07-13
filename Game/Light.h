#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

struct Light
{
	glm::vec3 position;
	glm::vec3 color;

	Light(glm::vec3 pos, glm::vec3 col) : position(pos), color(col) {}
};