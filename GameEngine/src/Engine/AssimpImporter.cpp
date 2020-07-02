#include "AssimpImporter.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "Mesh.h"

#include <iostream>

using namespace  Assimp;

const aiScene* AssimpImporter::ImportModel(std::string path, bool flipUV)
{
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene;
	if(flipUV)
		scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	else
		scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);
	// check for errors
	scene = importer.GetOrphanedScene();
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return nullptr;
	}
	
	return scene;
}

glm::mat4 AssimpImporter::AssimpTransformToGlm(aiMatrix4x4* from)
{
	glm::mat4 to;
		
	to[0][0] = (float)from->a1; to[0][1] = (float)from->b1;  to[0][2] = (float)from->c1; to[0][3] = (float)from->d1;
	to[1][0] = (float)from->a2; to[1][1] = (float)from->b2;  to[1][2] = (float)from->c2; to[1][3] = (float)from->d2;
	to[2][0] = (float)from->a3; to[2][1] = (float)from->b3;  to[2][2] = (float)from->c3; to[2][3] = (float)from->d3;
	to[3][0] = (float)from->a4; to[3][1] = (float)from->b4;  to[3][2] = (float)from->c4; to[3][3] = (float)from->d4;
	
	return to;
}
