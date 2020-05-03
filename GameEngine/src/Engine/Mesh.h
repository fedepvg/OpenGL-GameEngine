#ifndef MESH_H
#define MESH_H

#define EXPORTDLL _declspec(dllexport)

#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class LoadShader;

struct Vertex {
	// position
	glm::vec3 position;
	// normal
	glm::vec3 normal;
	// texCoords
	glm::vec2 texCoords;
	// tangent
	glm::vec3 tangent;
	// bitangent
	glm::vec3 bitangent;
};

struct TextureStruct {
	unsigned int id;
	string type;
	string path;
};

class EXPORTDLL Mesh {
public:
	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<TextureStruct> textures;
	unsigned int VAO;
	
	// constructor
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<TextureStruct> textures);

	// render the mesh
	void Draw(unsigned int program);

private:
	/*  Render data  */
	unsigned int VBO, EBO;

	// initializes all the buffer objects/arrays
	void SetupMesh();
};

#endif