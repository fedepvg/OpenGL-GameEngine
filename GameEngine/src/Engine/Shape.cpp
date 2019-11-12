#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shape.h"
#include "LoadShader.h"
#include "Texture.h"

Shape::Shape()
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	static const GLfloat g_vertex_buffer_data[] = {
		1.f, -1.f, 0.0f, 1.0f, 1.f, 1.0f, 1.0f, 0.0f,//+-
		-1.f, 1.f, 0.0f, 1.0f, 1.f, 1.0f, 0.0f, 1.0f,//-+
		-1.f, -1.f, 0.0f, 1.0f, 1.f, 1.0f, 0.0f, 0.0f,//--
		1.f, 1.f, 0.0f, 1.0f, 1.f, 1.0f, 1.0f, 1.0f,//++  
	};

	// Create a Vertex Buffer Object and copy the vertex data to it
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint elements[] =
	{
		0, 2, 3,
		1, 2, 3
	};

	// Create an element array
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	SetShader();
}

Shape::Shape(glm::vec3 pos, glm::vec3 setScale, Texture* tex) : Entity(pos, tex)
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	scale = setScale;

	static const GLfloat g_vertex_buffer_data[] = {
		1.f * setScale.x / 2, -1.f * setScale.y / 2, 0.0f, 1.0f, 1.f, 1.0f, 1.0f, 0.0f,//+-
		-1.f * setScale.x / 2, 1.f * setScale.y / 2, 0.0f, 1.0f, 1.f, 1.0f, 0.0f, 1.0f,//-+
		-1.f * setScale.x / 2, -1.f * setScale.y / 2, 0.0f, 1.0f, 1.f, 1.0f, 0.0f, 0.0f,//--
		1.f * setScale.x / 2, 1.f * setScale.y / 2, 0.0f, 1.0f, 1.f, 1.0f, 1.0f, 1.0f,//++  
	};

	// Create a Vertex Buffer Object and copy the vertex data to it
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint elements[] =
	{
		0, 2, 3,
		1, 2, 3
	};

	// Create an element array
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	SetShader();
}

Shape::~Shape()
{

}

void Shape::Render() 
{
	glUseProgram(programID);
	glBindVertexArray(vertexArray);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTexture());
	
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}