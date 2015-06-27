#pragma once

#include <glm/glm.hpp>

struct Vertex
{
	Vertex(glm::vec3 verts, glm::vec3 norms, glm::vec2 uvs) : vertPos(verts), vertNorm(norms), vertUV(uvs) {}
	Vertex() {}

	glm::vec3 vertPos;
	glm::vec3 vertNorm;
	glm::vec2 vertUV;

	glm::vec3 getVertPos() { return vertPos; }
	glm::vec3 getVertNorm() { return vertNorm; }
	glm::vec2 getVertUV() { return vertUV; }

	void setVertPos(glm::vec3 newPos) { vertPos = newPos; }
	void setVertNorm(glm::vec3 newNorm) { newNorm = vertNorm; }
	void setVertUV(glm::vec2 newUV) { newUV = vertUV; }
};