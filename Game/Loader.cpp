#include "Loader.h"
#include "Error.h"
#include "PicoPNG.h"

#include <iostream>
#include <fstream>
#include <sstream>

Loader::Loader()
{
}

GLuint Loader::loadShaders(const std::string& vertexFile, const std::string& fragmentFile)
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//Read Vertex shader from file
	std::string vertexCode;
	std::ifstream vertexStream(vertexFile, std::ios::in);
	if (vertexStream.is_open()) {
		std::string line;
		while (std::getline(vertexStream, line))
			vertexCode += "\n" + line;
		vertexStream.close();
	}

	//Read fragment shader from file
	std::string fragmentCode;
	std::ifstream fragmentStream(fragmentFile, std::ios::in);
	if (fragmentStream.is_open()) {
		std::string line;
		while (std::getline(fragmentStream, line))
			fragmentCode += "\n" + line;
		fragmentStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	//Compile vertex shader
	printf("Compiling vertex shader\n");
	const char* vertexPointer = vertexCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexPointer, NULL);
	glCompileShader(vertexShaderID);

	//Check vertex shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(vertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

	//Compile fragment shader
	printf("Compiling fragment shader\n");
	const char* fragmentPointer = fragmentCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentPointer, NULL);
	glCompileShader(fragmentShaderID);

	//Check fragment shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(fragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

	//Link program
	printf("Linking program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	//Check program
	glGetProgramiv(programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(InfoLogLength, int(1));
	glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}

GLTexture Loader::loadPNG(std::string filePath)
{
	GLTexture texture = {};

	std::vector<unsigned char> in;
	std::vector<unsigned char> out;

	unsigned long width, height;

	if (loadFile(filePath, in) == false) {
		fatalError("Failed to load file to buffer");
	}

	printf("Loading texture...\n");

	int errorCode = decodePNG(out, width, height, in.data(), in.size());

	if (errorCode != 0) {
		fatalError("decodePNG failed with error: " + std::to_string(errorCode));
	}

	glGenTextures(1, &(texture.id));

	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, out.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width;
	texture.height = height;

	return texture;
}

//TODO: Make loadObJ return an asset or something
bool Loader::loadOBJ(const char* filePath, std::vector<Vertex>& vertices)
{
	printf("Loading OBJ file %s...\n", filePath);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE * file = fopen(filePath, "r");
	if (file == NULL){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while (true){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9){
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}
	
	std::vector<glm::vec3> verts, norms;
	std::vector<glm::vec2> uvs;

	// For each vertex of each triangle
	for (unsigned int i = 0; i<vertexIndices.size(); i++){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		vertices.emplace_back(vertex, normal, uv);
	}

	return true;
}

bool Loader::loadFile(const std::string& fileName, std::vector<unsigned char>& buffer)
{
	//open file
	std::ifstream file(fileName, std::ios::binary);
	if (file.fail()) {
		fatalError("Failed to read in file: " + fileName);
		return false;
	}

	//get size of file
	long size;
	file.seekg(0, std::ios::end);
	size = file.tellg();

	//reset to beginning
	file.seekg(0, std::ios::beg);

	//resize buffer
	size -= file.tellg();
	buffer.resize(size);

	//read file to buffer
	file.read((char*)&(buffer[0]), size);

	file.close();

	return true;
}

Loader::~Loader()
{
}
