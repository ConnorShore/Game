#include "ShaderProgram.h"

#include <vector>
#include <fstream>


ShaderProgram::ShaderProgram()
{
}

//GLuint ShaderProgram::loadShaders(const std::string & vertexFile, const std::string & fragmentFile)
GLuint ShaderProgram::loadShader(const std::string& file, GLuint type)
{
	//GLuint _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	//GLuint _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//read shader from file
	std::string input;
	std::ifstream shaderStream(file, std::ios::in);
	if (shaderStream.is_open()) {
		std::string line;
		while (std::getline(shaderStream, line))
			input += "\n" + line;
		shaderStream.close();
	}

	GLuint shaderID = glCreateShader(type);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	//Compile shader
	printf("Compiling vertex shader\n");
	const char* shaderPointer = input.c_str();
	glShaderSource(shaderID, 1, &shaderPointer, NULL);
	glCompileShader(shaderID);

	//Check shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &ShaderErrorMessage[0]);

	return shaderID;

	////Read fragment shader from file
	//std::string fragmentCode;
	//std::ifstream fragmentStream(fragmentFile, std::ios::in);
	//if (fragmentStream.is_open()) {
	//	std::string line;
	//	while (std::getline(fragmentStream, line))
	//		fragmentCode += "\n" + line;
	//	fragmentStream.close();
	//}

	//GLint Result = GL_FALSE;
	//int InfoLogLength;

	////Compile vertex shader
	//printf("Compiling vertex shader\n");
	//const char* vertexPointer = vertexCode.c_str();
	//glShaderSource(_vertexShaderID, 1, &vertexPointer, NULL);
	//glCompileShader(_vertexShaderID);

	////Check vertex shader
	//glGetShaderiv(_vertexShaderID, GL_COMPILE_STATUS, &Result);
	//glGetShaderiv(_vertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	//std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	//glGetShaderInfoLog(_vertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	//fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

	////Compile fragment shader
	//printf("Compiling fragment shader\n");
	//const char* fragmentPointer = fragmentCode.c_str();
	//glShaderSource(_fragmentShaderID, 1, &fragmentPointer, NULL);
	//glCompileShader(_fragmentShaderID);

	////Check fragment shader
	//glGetShaderiv(_fragmentShaderID, GL_COMPILE_STATUS, &Result);
	//glGetShaderiv(_fragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	//std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	//glGetShaderInfoLog(_fragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	//fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

	////Link program
	//printf("Linking program\n");
	//GLuint _programID = glCreateProgram();
	//glAttachShader(_programID, _vertexShaderID);
	//glAttachShader(_programID, _fragmentShaderID);
	//glLinkProgram(_programID);

	////Check program
	//glGetProgramiv(_programID, GL_LINK_STATUS, &Result);
	//glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	//std::vector<char> ProgramErrorMessage(InfoLogLength, int(1));
	//glGetProgramInfoLog(_programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	//fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	//glDetachShader(_programID, _vertexShaderID);
	//glDetachShader(_programID, _fragmentShaderID);

	//glDeleteShader(_vertexShaderID);
	//glDeleteShader(_fragmentShaderID);

	//return _programID;
}

void ShaderProgram::init(const std::string& vertexFile, const std::string& fragmentFile)
{
	_vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
	_fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	_programID = glCreateProgram();

	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);
	glLinkProgram(_programID);
	glValidateProgram(_programID);

	//Check program
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetProgramiv(_programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(InfoLogLength, int(1));
	glGetProgramInfoLog(_programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
}

void ShaderProgram::start()
{
	glUseProgram(_programID);
}

void ShaderProgram::stop()
{
	glUseProgram(0);
}

void ShaderProgram::cleanUp()
{
	stop();

	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
	glDeleteProgram(_programID);
}

void ShaderProgram::bindAttribute(int attrib, std::string name)
{
	glBindAttribLocation(_programID, attrib, name.c_str());
}

GLuint ShaderProgram::getUniformLocation(std::string name)
{
	return glGetUniformLocation(_programID, name.c_str());
}

void ShaderProgram::loadInt(int location, int value)
{
	glUniform1i(location, value);
}

void ShaderProgram::loadFloat(int location, float value)
{
	glUniform1f(location, value);
}

void ShaderProgram::loadVector3f(int location, glm::vec3 vector)
{
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::loadMatrix4f(int location, glm::mat4 matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &(matrix[0][0]));
}

ShaderProgram::~ShaderProgram()
{
}