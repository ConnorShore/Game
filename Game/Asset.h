#pragma once

#include "Model.h"
#include "StaticShader.h"

#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Asset
{
public:
	Asset(glm::vec3& position, float rotation = 0.0f, glm::vec3& rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f), float scale = 1.0f);
	~Asset();

	void init(const std::string& modelFile, const std::string& textureFile);
	void render(StaticShader shader);
	glm::mat4 createModelMatrix();

	//Getters
	Model getModel() { return model_; }
	GLTexture getTexture() const { return model_.getTexture(); }

	glm::vec3 getPosition() const { return position_; }
	glm::vec3 getRotationAxis() const { return rotationAxis_; }

	float getScale() const { return scale_; }
	float getRotation() const { return rotation_; }

	//Setters
	void setPosition(glm::vec3& newPos) { position_ = newPos; }
	void setRotation(float angle, glm::vec3 axis) { rotation_ = angle; rotationAxis_ = axis; }
	void setRotation(float angle) { rotation_ = angle; rotationAxis_ = glm::vec3(0, 1, 0); }
	void setScale(float newScale) { scale_ = newScale; }

protected:
	float scale_, rotation_;
	glm::vec3 position_, rotationAxis_;
	Model model_;

private:
	GLuint _vaoID, _vertexBuffer, _normalBuffer, _uvBuffer;
};