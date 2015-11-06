#pragma once

#include <vector>

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

private:
	const std::string VERTEX_FILE = "Shaders/staticShader.vert";
	const std::string FRAGMENT_FILE = "Shaders/staticShader.frag";

	int _textureLoc;
};