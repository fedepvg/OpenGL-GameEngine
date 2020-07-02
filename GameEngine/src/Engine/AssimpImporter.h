#ifndef  ASSIMP_IMPORTER_H
#define ASSIMP_IMPORTER_H

#include <string>
#include <assimp/scene.h>   
#include <glm/mat4x4.hpp>

class Mesh;

class AssimpImporter
{
public:
	static const aiScene* ImportModel(std::string path, bool flipUV);
	static glm::mat4 AssimpTransformToGlm(aiMatrix4x4* from);
};

#endif // ! ASSIMP_IMPORTER
