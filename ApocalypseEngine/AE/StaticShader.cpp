#include "StaticShader.h"

#include <glm/glm.hpp>
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

	for (int i = 0; i < MAX_LIGHTS; i++) {
		_lightPosLoc[i] = getUniformLocation("lightPosition[" + std::to_string(i) + "]");
		_lightColLoc[i] = getUniformLocation("lightColor[" + std::to_string(i) + "]");
		_lightAttenLoc[i] = getUniformLocation("attenuation[" + std::to_string(i) + "]");
	}
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

void StaticShader::loadLights(std::vector<Light> lights)
{
	for (int i = 0; i < MAX_LIGHTS; i++) {
		if (i < lights.size()) {
			loadVector3f(_lightPosLoc[i], lights[i].getPosition());
			loadVector3f(_lightColLoc[i], lights[i].getColor());
			loadVector3f(_lightAttenLoc[i], lights[i].getAttenuation());
		}
		else {
			loadVector3f(_lightPosLoc[i], glm::vec3(0.0f, 0.0f, 0.0f));
			loadVector3f(_lightColLoc[i], glm::vec3(0.0f, 0.0f, 0.0f));
			loadVector3f(_lightAttenLoc[i], glm::vec3(1.0f, 0.0f, 0.0f));
		}
	}
}

StaticShader::~StaticShader()
{
}