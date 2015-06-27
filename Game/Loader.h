#pragma once

#include "GLTexture.h"
#include "Vertex.h"

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Loader
{
public:
	Loader();
	~Loader();

	static GLuint loadShaders(const std::string& vertexFile, const std::string& fragmentFile);
	static GLTexture loadPNG(std::string filePath);
	static bool loadOBJ(const char* filePath, std::vector<Vertex>& vertices);
	//static bool loadOBJ(const char* filePath, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& uvs);
	static bool loadFile(const std::string& fileName, std::vector<unsigned char>& buffer);


};

