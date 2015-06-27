#pragma once

#include "Vertex.h"
#include "Loader.h"

#include <vector>
#include <string>
#include <glm/glm.hpp>


class Model
{
public:
	Model(const std::string& modelName, const std::string& modelFile);
	~Model();

	std::string getModelName() const { return name; }

	void setModelName(std::string newName) { name = newName; }

private:
	std::string name;
	std::vector<Vertex> vertices;
};

