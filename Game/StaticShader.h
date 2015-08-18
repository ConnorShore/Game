#pragma once

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
	void loadLight(Light light);
	void loadShine(float level, float damp);

private:
	const std::string VERTEX_FILE = "Shaders/staticShader.vert";
	const std::string FRAGMENT_FILE = "Shaders/staticShader.frag";

	int _viewMatrixLoc, _projectionMatrixLoc, _modelMatrixLoc, _textureLoc, _lightPosLoc, _lightColLoc, _shineLevLoc, _shineDampLoc;
};