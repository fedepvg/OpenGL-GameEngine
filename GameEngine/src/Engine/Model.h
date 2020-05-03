#ifndef MODEL_H
#define MODEL_H

#define EXPORTDLL _declspec(dllexport)

#include "Mesh.h"
#include "assimp/scene.h"

#include <vector>

using namespace std;

class Texture;

class EXPORTDLL Model
{
public:
	/*  Model Data */
	vector<TextureStruct> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;

	/*  Functions   */
	// constructor, expects a filepath to a 3D model.
	Model(string const &path);

	void LoadModel(string const &path);
	
	// draws the model, and thus all its meshes
	void Draw(/*Shader shader*/);

private:
	const aiScene* scene;
	unsigned int programID;
	/*  Functions   */
	// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.

	//void loadModel(string const &path)
	//{
	//	// read file via ASSIMP
	//	Assimp::Importer importer;
	//	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	//	// check for errors
	//	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	//	{
	//		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
	//		return;
	//	}
	//	// retrieve the directory path of the filepath
	//	directory = path.substr(0, path.find_last_of('/'));
	//
	//	// process ASSIMP's root node recursively
	//	ProcessNode(scene->mRootNode, scene);
	//}

	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void ProcessNode(aiNode *node, const aiScene *scene);

	Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);

	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	vector<TextureStruct> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif