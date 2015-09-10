#include "Model.h"
#include "Error.h"


Model::Model()
{

}

bool Model::load(const std::string& modelFile, const std::string& textureFile)
{
	int errorCode = Loader::loadOBJ(modelFile.c_str(), _vertices);

	if (errorCode  == false) {
		fatalError("Failed to load model: " + modelFile);
		return false;
	}

	_texture = Loader::loadPNG(textureFile);

	return true;
}

Model::~Model()
{
}
