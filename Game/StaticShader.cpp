#include "StaticShader.h"
#include "Asset.h"

#include <glm/gtc/matrix_transform.hpp>

StaticShader::StaticShader()
{
}

void StaticShader::bindAttributes()
{
	bindAttribute(0, "vertexPosition");
	bindAttribute(1, "vertexUV");
}

void StaticShader::getUniformLocations()
{
	_cameraMatrixLoc = getUniformLocation("cameraMatrix");
	_modelMatrixLoc = getUniformLocation("modelMatrix");
	_textureLoc = getUniformLocation("myTexture");
}

void StaticShader::loadCameraMatrix(Camera camera)
{
	glm::mat4 camMatrix = camera.getMatrix();
	loadMatrix4f(_cameraMatrixLoc, camMatrix);
}

void StaticShader::loadModelMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_modelMatrixLoc, matrix);
}

void StaticShader::loadTexture()
{
	glUniform1i(_textureLoc, 0);
}

StaticShader::~StaticShader()
{
}