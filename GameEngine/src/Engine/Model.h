#ifndef MODEL_H
#define MODEL_H

#define EXPORTDLL _declspec(dllexport)

#include "Mesh.h"
#include "assimp/scene.h"

#include <vector>

using namespace std;

class Texture;
class Shader;

class EXPORTDLL Model
{
public:
	/*  Model Data */
	vector<TextureStruct> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;
	Shader* shader;

	/*  Functions   */
	// constructor, expects a filepath to a 3D model.
	Model(string const &path, Shader* shader);

	void LoadModel(string const &path);
	
	// draws the model, and thus all its meshes
	void Draw();

private:
	const aiScene* scene;
	
	/*  Functions   */
	// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.

	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void ProcessNode(aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);

	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	vector<TextureStruct> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif