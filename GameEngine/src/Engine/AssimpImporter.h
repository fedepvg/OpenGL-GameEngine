#ifndef  ASSIMP_IMPORTER_H
#define ASSIMP_IMPORTER_H

#include <string>
#include <assimp/scene.h>   

class Mesh;

class AssimpImporter
{
public:
	bool DoTheImportThing(const std::string& pFile);
	const aiScene* ImportModel(std::string path);
};

#endif // ! ASSIMP_IMPORTER
