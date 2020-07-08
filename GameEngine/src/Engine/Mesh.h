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
#include "Entity3D.h"

using namespace std;

class LoadShader;
class Shader;

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

class EXPORTDLL Mesh : public Entity3D
{
public:
	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<TextureStruct> textures;
	unsigned int VAO;
	
	// constructor
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<TextureStruct> textures, Entity3D* newParent, Shader* shader);

	int GetElementsSize();
	unsigned int GetVertexArray();
	vector<TextureStruct> GetTextures();
	virtual void GetVertexPositions(vector<glm::vec3> &vertexVector);
	Bounds UpdateModelMatAndBoundingBox() override;

private:
	/*  Render data  */
	unsigned int VBO, EBO;

	// initializes all the buffer objects/arrays
	void SetupMesh();
};

#endif