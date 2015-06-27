#pragma once

#include "Model.h"

#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Asset
{
public:
	Asset();
	~Asset();

	void init(const std::string& modelFile, const std::string& textureFile, glm::vec3 position, float scale);
	void render();
	void bind();
	void unbind();

	//virtual void init(glm::vec3 position, glm::vec3 scale) = 0;
	//virtual void update() = 0;
	//virtual void render() = 0;
	//virtual void cleanUp() = 0;

	Model getModel() { return model_; }
	GLTexture getTexture() const { return model_.getTexture(); }

protected:
	float scale_;
	glm::vec3 position_;
	Model model_;

private:
	GLuint _vaoID, _vertexBuffer, _normalBuffer, _uvBuffer;
};

