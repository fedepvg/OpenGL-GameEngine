#include "BoundingBox.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Shader.h"

Shader* BoundingBox::shader = nullptr;

BoundingBox::BoundingBox()
{
	//for (int i = 0; i < BOXVERTICES; i++)
	//{
	//	vertex[i] = glm::vec3(0.0f, 0.0f, 0.0f);
	//}
	if (shader == nullptr)
		shader = new Shader("../src/Engine/SimpleVertexShader.vertexshader", "../src/Engine/SimpleFragmentShader.fragmentshader");
	
	GLushort cubeIndices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};
	for (int i = 0; i < 36; i++)
		indices.push_back(cubeIndices[i]);
	isVisible = false;
	CreateBuffers();
	Setup();
}

void BoundingBox::CalculateBoundingBox(Bounds bounds, glm::mat4 modelMat)
{
	glm::vec3 boundingBoxVertex[BOXVERTICES] =
	{
		glm::vec3(bounds.minX, bounds.minY, bounds.maxZ),
		glm::vec3(bounds.maxX, bounds.minY, bounds.maxZ),
		glm::vec3(bounds.maxX, bounds.maxY, bounds.maxZ),
		glm::vec3(bounds.minX, bounds.maxY, bounds.maxZ),
		glm::vec3(bounds.minX, bounds.minY, bounds.minZ),
		glm::vec3(bounds.maxX, bounds.minY, bounds.minZ),
		glm::vec3(bounds.maxX, bounds.maxY, bounds.minZ),
		glm::vec3(bounds.minX, bounds.maxY, bounds.minZ),
	};

	for (int i = 0; i < BOXVERTICES; i++)
		vertex[i] = modelMat * glm::vec4(boundingBoxVertex[i],1.f);

	Setup();
}

void BoundingBox::CreateBuffers()
{
	// create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void BoundingBox::Setup()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);
	
	// vertex Positions
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	glBindVertexArray(0);
}

void BoundingBox::Draw(glm::mat4 viewMat, glm::mat4 projMat)
{
	if(!isVisible)
		return;
	shader->Use();
	shader->SetMat4("view", viewMat);
	shader->SetMat4("proj", projMat);
	shader->SetMat4("model", glm::mat4(1.0f));	

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(VAO);
	
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
