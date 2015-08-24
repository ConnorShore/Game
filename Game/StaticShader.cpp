#include "StaticShader.h"

#include <glm/gtc/matrix_transform.hpp>

StaticShader::StaticShader()
{
}

void StaticShader::bindAttributes()
{
	bindAttribute(0, "vertexPosition");
	bindAttribute(1, "vertexUV");
	bindAttribute(2, "vertexNormal");
}

void StaticShader::getUniformLocations()
{
	_viewMatrixLoc = getUniformLocation("viewMatrix");
	_projectionMatrixLoc = getUniformLocation("projectionMatrix");
	_modelMatrixLoc = getUniformLocation("modelMatrix");
	_textureLoc = getUniformLocation("myTexture");
	_lightPosLoc = getUniformLocation("lightPosition");
	_lightColLoc = getUniformLocation("lightColor");
}

void StaticShader::loadViewMatrix(Camera camera)
{
	glm::mat4 view = camera.getViewMatrix();
	loadMatrix4f(_viewMatrixLoc, view);
}

void StaticShader::loadProjectionMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_projectionMatrixLoc, matrix);
}

void StaticShader::loadModelMatrix(glm::mat4 matrix)
{
	loadMatrix4f(_modelMatrixLoc, matrix);
}

void StaticShader::loadTexture()
{
	glUniform1i(_textureLoc, 0);
}

void StaticShader::loadLight(Light light)
{
	loadVector3f(_lightPosLoc, light.getPosition());
	loadVector3f(_lightColLoc, light.getColor());
}

StaticShader::~StaticShader()
{
}