#pragma once

#include <vector>

#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	~StaticShader();

	void bindAttributes() override;
	void getUniformLocations() override;

	void loadViewMatrix(Camera camera);
	void loadProjectionMatrix(glm::mat4 matrix);
	void loadModelMatrix(glm::mat4 matrix);
	void loadTexture();
	void loadLights(std::vector<Light> lights);

private:
	const std::string VERTEX_FILE = "Shaders/staticShader.vert";
	const std::string FRAGMENT_FILE = "Shaders/staticShader.frag";

	const static int MAX_LIGHTS = 4;

	int _viewMatrixLoc, _projectionMatrixLoc, _modelMatrixLoc, _textureLoc;

	int _lightPosLoc[MAX_LIGHTS];
	int _lightColLoc[MAX_LIGHTS];
};