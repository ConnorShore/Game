#include "Asset.h"


Asset::Asset(Model model, glm::vec3 position, float scale) : position_(position), scale_(scale), model_(model), _vaoID(0)
{
}

void Asset::createVAO()
{
	if (_vaoID = 0) glGenVertexArrays(1, &_vaoID);
	glBindVertexArray(_vaoID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);	//position
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);	//color
	glVertexAttribPointer(2, 2, GL_UNSIGNED_INT, GL_FALSE, 0, (void*)0);	//uv
}

void Asset::init()
{

}

void Asset::render()
{

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
