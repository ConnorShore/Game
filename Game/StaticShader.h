#pragma once

#include "ShaderProgram.h"
#include "Camera.h"

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	~StaticShader();

	void bindAttributes() override;
	void getUniformLocations() override;

	void loadCameraMatrix(Camera camera);
	void loadModelMatrix(glm::mat4 matrix);
	void loadTexture();

private:
	const std::string VERTEX_FILE = "Shaders/staticShader.vert";
	const std::string FRAGMENT_FILE = "Shaders/staticShader.frag";

	int _cameraMatrixLoc, _modelMatrixLoc, _textureLoc;
};

