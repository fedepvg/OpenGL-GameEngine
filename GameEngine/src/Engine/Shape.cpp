#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shape.h"
#include "LoadShader.h"

Shape::Shape()
{
	static const GLfloat g_vertex_buffer_data[] = {
		0.4f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f, //+-
		-0.4f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f, //-+
		-0.4f, -0.4f, 0.0f, 1.0f, 0.8f, 0.0f, //--
		0.4f, 0.4f, 0.0f, 1.0f, 0.8f, 0.0f, //++  
	};

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


	GLuint elements[] =
	{
		0, 2, 3,
		1, 2, 3
	};

	// Create an element array
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

}

Shape::~Shape()
{

}