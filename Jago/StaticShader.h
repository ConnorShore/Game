#pragma once

#include <vector>
#include <glm/glm.hpp>

#include <ApocalypseEngine\ShaderProgram.h>
#include <ApocalypseEngine\Camera.h>
#include <ApocalypseEngine\BaseLight.h>

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	~StaticShader();

	void bindAttributes() override;
	void getUniformLocations() override;

	void loadTexture();
	void loadPMatrix(glm::mat4 matrix);

private:
	int _textureLoc, _pMatrixLoc;
};