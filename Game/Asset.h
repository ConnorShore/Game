#pragma once

#include "Model.h"

#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Asset
{
public:
	Asset(Model model, glm::vec3 position, float scale);
	~Asset();

	void createVAO();

	void init();
	void render();
	void unbind();

	//virtual void init(glm::vec3 position, glm::vec3 scale) = 0;
	//virtual void update() = 0;
	//virtual void render() = 0;
	//virtual void cleanUp() = 0;

protected:
	float scale_;
	glm::vec3 position_;
	Model model_;

private:
	GLuint _vaoID;
};

