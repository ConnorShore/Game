#pragma once

#include "Vertex.h"
#include "Loader.h"
#include "Model.h"
#include "GLTexture.h"

#include <vector>
#include <string>
#include <glm/glm.hpp>


class Model
{
public:
	Model();
	~Model();

	bool load(const std::string& modelFile, const std::string& textureFile);

	std::vector<glm::vec3> getVertices() {
		std::vector<glm::vec3> verts;
		for (int i = 0; i < _vertices.size(); i++) {
			verts.push_back(_vertices[i].getVertPos());
		}
		return verts;
	}

	std::vector<glm::vec3> getNormals() {
		std::vector<glm::vec3> norms;
		for (int i = 0; i < _vertices.size(); i++) {
			norms.push_back(_vertices[i].getVertNorm());
		}
		return norms;
	}

	std::vector<glm::vec2> getUVs() {
		std::vector<glm::vec2> uvs;
		for (int i = 0; i < _vertices.size(); i++) {
			uvs.push_back(_vertices[i].getVertUV());
		}
		return uvs;
	}

	std::vector<Vertex> getVertArray() const { return _vertices; }

	GLTexture getTexture() const { return _texture; }

private:
	std::vector<Vertex> _vertices;
	GLTexture _texture; 
};

