#pragma once

#include <ApocalypseEngine\ShaderProgram.h>

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

