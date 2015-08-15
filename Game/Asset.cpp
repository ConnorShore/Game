#include "Asset.h"
#include "Error.h"

#include <glm/gtc/matrix_transform.hpp>


Asset::Asset(glm::vec3& position) : _vaoID(0), position_(position)
{
}

void Asset::init(const std::string& modelFile, const std::string& textureFile, float scale)
{
	if (_vaoID = 0) glGenVertexArrays(1, &_vaoID);
	glBindVertexArray(_vaoID);

	scale_ = scale;

	bool res = model_.load(modelFile, textureFile);
	if (res == false) fatalError("Failed to load model: " + modelFile);

	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, model_.getVertices().size() * sizeof(glm::vec3), &model_.getVertices()[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, model_.getNormals().size() * sizeof(glm::vec3), &model_.getNormals()[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, model_.getUVs().size() * sizeof(glm::vec2), &model_.getUVs()[0], GL_STATIC_DRAW);
}

void Asset::render()
{
	glDrawArrays(GL_TRIANGLES, 0, model_.getVertArray().size());
}

void Asset::bind()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void Asset::unbind()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

Asset::~Asset()
{
}