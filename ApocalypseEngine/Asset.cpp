#include "Asset.h"
#include "Error.h"

#include <glm/gtc/matrix_transform.hpp>

Asset::Asset(glm::vec3& position, float rotation /*0.0f*/, glm::vec3& rotationAxis /*glm::vec3(0.0f,1.0f,0.0f)*/, float scale /*1.0f*/)
	: _vaoID(0), position_(position), rotation_(rotation), rotationAxis_(rotationAxis), scale_(scale)
{
}

void Asset::init(const std::string& modelFile, const std::string& textureFile)
{

	if (_vaoID = 0) glGenVertexArrays(1, &_vaoID);
	glBindVertexArray(_vaoID);

	bool res = model_.load(modelFile, textureFile);
	if (res == false) fatalError("Failed to load model: " + modelFile);

	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, model_.getVertices().size() * sizeof(glm::vec3), &model_.getVertices()[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, model_.getUVs().size() * sizeof(glm::vec2), &model_.getUVs()[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, model_.getNormals().size() * sizeof(glm::vec3), &model_.getNormals()[0], GL_STATIC_DRAW);
}

void Asset::render(StaticShader shader)
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, getTexture().id);

	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, model_.getVertArray().size());

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

glm::mat4 Asset::createModelMatrix()
{
	glm::mat4 model;
	model = glm::translate(model, getPosition());
	model = glm::rotate(model, getRotation(), getRotationAxis());
	model = glm::scale(model, glm::vec3(getScale(), getScale(), getScale()));

	return model;
}

Asset::~Asset()
{
}