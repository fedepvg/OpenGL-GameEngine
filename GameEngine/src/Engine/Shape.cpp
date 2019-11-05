#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shape.h"
#include "LoadShader.h"

Shape::Shape()
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	static const GLfloat g_vertex_buffer_data[] = {
		0.4f, -0.4f, 0.0f, 1.0f, 1.f, 1.0f, 1.0f, 0.0f,//+-
		-0.4f, 0.4f, 0.0f, 1.0f, 1.f, 1.0f, 0.0f, 1.0f,//-+
		-0.4f, -0.4f, 0.0f, 1.0f, 1.f, 1.0f, 0.0f, 0.0f,//--
		0.4f, 0.4f, 0.0f, 1.0f, 1.f, 1.0f, 1.0f, 1.0f,//++  
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
	//glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	//glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	//glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindVertexArray(vertexArray);
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}