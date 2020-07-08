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
	if(shader == nullptr)
		shader = new Shader("../src/Engine/SimpleVertexShader.vertexshader", "../src/Engine/SimpleFragmentShader.fragmentshader");

	static const GLushort cubeIndices[] = {
	0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
	};
	for (int i = 0; i < 14; i++)
		indices.push_back(cubeIndices[i]);

	CreateBuffers();
	Setup();
}

void BoundingBox::CalculateBoundingBox(Bounds bounds, glm::mat4 modelMat)
{
	glm::vec3 boundingBoxVertex[BOXVERTICES] =
	{
		glm::vec3(bounds.minX, bounds.minY, bounds.minZ),
		glm::vec3(bounds.minX, bounds.maxY, bounds.minZ),
		glm::vec3(bounds.minX, bounds.minY, bounds.maxZ),
		glm::vec3(bounds.minX, bounds.maxY, bounds.maxZ),
		glm::vec3(bounds.maxX, bounds.minY, bounds.minZ),
		glm::vec3(bounds.maxX, bounds.maxY, bounds.minZ),
		glm::vec3(bounds.maxX, bounds.minY, bounds.maxZ),
		glm::vec3(bounds.maxX, bounds.maxY, bounds.maxZ)
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
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	glBindVertexArray(0);
}

void BoundingBox::Draw(glm::mat4 viewMat, glm::mat4 projMat)
{
	shader->SetMat4("view", viewMat);
	shader->SetMat4("proj", projMat);
	shader->SetMat4("model", glm::mat4(1.0f));
	
	shader->Use();

	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);

	glBindVertexArray(VAO);
	// Draw the box
	glDrawElements(GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
	// Turn off wireframe mode
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
}
