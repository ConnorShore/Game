#pragma once

#include "Model.h"

#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Asset
{
public:
	Asset(glm::vec3& position);
	~Asset();

	void init(const std::string& modelFile, const std::string& textureFile, float scale);
	void render();
	void bind();
	void unbind();

	Model getModel() { return model_; }
	GLTexture getTexture() const { return model_.getTexture(); }
	glm::vec3 getPosition() const { return position_; }
	glm::mat4 getModelMatrix() const { return _modelMatrix; }

	void setPosition(glm::vec3& newPos) { position_ = newPos;}

protected:
	float scale_;
	glm::vec3 position_;
	Model model_;

private:
	GLuint _vaoID, _vertexBuffer, _normalBuffer, _uvBuffer;

	glm::mat4 _modelMatrix;
};