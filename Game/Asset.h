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

	void initAsset(const std::string& modelFile, const std::string& textureFile, glm::vec3 position, float scale);
	void render();
	void bind();
	void unbind();

	Model getModel() { return model_; }
	GLTexture getTexture() const { return model_.getTexture(); }
	glm::vec3 getPosition() const { return position_; }

	void setPosition(glm::vec3& newPos) { position_ = newPos; }

private:
	GLuint _vaoID, _vertexBuffer, _normalBuffer, _uvBuffer;
	float scale_;
	glm::vec3 position_;
	Model model_;
};