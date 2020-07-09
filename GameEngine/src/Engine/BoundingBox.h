#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#define EXPORTDLL _declspec(dllexport)

#include <glm/glm.hpp>

#include <vector>
#include "Entity3D.h"

#define	BOXVERTICES 8

class EXPORTDLL BoundingBox
{
	glm::vec3 vertex[BOXVERTICES];
	static class Shader* shader;
	unsigned int VAO, VBO, EBO;
	std::vector<unsigned int> indices;
	bool isVisible = false;

public:
	BoundingBox();
	void CalculateBoundingBox(Bounds bounds, glm::mat4 modelMat);
	void CreateBuffers();
	void Setup();
	void Draw(glm::mat4 viewMat, glm::mat4 projMat);
	void SetVisibility(bool visibility) { isVisible = visibility; }
	bool GetVisibility() const { return isVisible; }
	glm::vec3 GetVertex(unsigned int index);
};

#endif