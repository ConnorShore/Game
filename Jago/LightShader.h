#pragma once

#include <vector>
#include <glm/glm.hpp>

#include <ApocalypseEngine\ShaderProgram.h>
#include <ApocalypseEngine\Camera.h>
#include <ApocalypseEngine\BaseLight.h>

class LightShader : public ShaderProgram
{
public:
	LightShader();
	~LightShader();

	void bindAttributes() override;
	void getUniformLocations() override;

	void loadPMatrix(glm::mat4 matrix);

private:
	int _pMatrixLoc;
};