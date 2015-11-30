#include "LightShader.h"



LightShader::LightShader()
{
}


LightShader::~LightShader()
{
}

void LightShader::bindAttributes()
{
	bindAttribute(0, "vertexPosition");
	bindAttribute(1, "vertexColor");
	bindAttribute(2, "vertexUV");
}

void LightShader::getUniformLocations()
{
	_pMatrixLoc = getUniformLocation("P");
}

void LightShader::loadPMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_pMatrixLoc, matrix);
}