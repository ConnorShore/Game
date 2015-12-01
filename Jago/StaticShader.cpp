#include "StaticShader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

StaticShader::StaticShader()
{

}

void StaticShader::bindAttributes()
{
	bindAttribute(0, "vertexPosition");
	bindAttribute(1, "vertexColor");
	bindAttribute(2, "vertexUV");
}

void StaticShader::getUniformLocations()
{
	_textureLoc = getUniformLocation("myTexture");
	_pMatrixLoc = getUniformLocation("P");
}

void StaticShader::loadPMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_pMatrixLoc, matrix);
}

void StaticShader::loadTexture()
{
	glUniform1i(_textureLoc, 0);
}

StaticShader::~StaticShader()
{
}