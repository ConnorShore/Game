#include "Model.h"
#include "Error.h"


Model::Model(const std::string& modelName, const std::string& modelFile) : name(modelName)
{
	//int errorCode = Loader::loadOBJ(modelFile.c_str(), vertices);

	//if (errorCode  == false) {
	//	fatalError("Failed to load model: " + name);
	//}
}


Model::~Model()
{
}
