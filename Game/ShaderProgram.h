#pragma once

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void init(const std::string& vertexFile, const std::string& fragmentFile);
	void start();
	void stop();
	void cleanUp();

protected:
	GLuint getUniformLocation(std::string name);
	void bindAttribute(int attrib, std::string name);
	void loadInt(int location, int value);
	void loadFloat(int location, float value);
	void loadVector3f(int location, glm::vec3 vector);
	void loadMatrix4f(int location, glm::mat4 matrix);

	virtual void bindAttributes() = 0;
	virtual void getUniformLocations() = 0;

private:
	GLuint _programID;
	GLuint _vertexShaderID, _fragmentShaderID;

	GLuint loadShader(const std::string& file, GLuint type);
};