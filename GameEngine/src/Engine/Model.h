#ifndef MODEL_H
#define MODEL_H

#define EXPORTDLL _declspec(dllexport)

#include "Mesh.h"

#include <vector>

using namespace std;

class Texture;
class Shader;

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;

class EXPORTDLL Model : public Entity3D
{
public:
	/*  Model Data */
	vector<TextureStruct> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	//vector<class Entity3D*> nodes;
	Entity3D* root;
	string directory;
	Shader* shader;

	/*  Functions   */
	// constructor, expects a filepath to a 3D localModel.
	Model(string const &path, Shader* shader, bool flipUV = true);

	void LoadModel(string const &path, bool flipUV);

private:
	//const aiScene* scene;
	
	/*  Functions   */
	// loads a localModel with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.

	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void ProcessNode(aiNode *node, const aiScene *scene, Entity3D* parent);// , vector<glm::vec3> &vertices);
	Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene, Entity3D* parent, Shader* shader);

	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	vector<TextureStruct> LoadMaterialTextures(aiMaterial *mat, int type, string typeName);
	//glm::mat4 modelMat;
};

#endif