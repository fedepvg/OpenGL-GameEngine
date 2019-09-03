#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "LoadShader.h"
#include "Renderer.h"
#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::SetShader()
{
	//load shaders
	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	//use shader
	glUseProgram(programID);

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(programID, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	GLint colAttrib = glGetAttribLocation(programID, "customColor");
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(colAttrib);

	 uniModel = glGetUniformLocation(programID, "myMatrix");
	 myMatrix = glm::translate(glm::vec3(1.4f, 0.0f, 0.0f));
	 glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(myMatrix));
}

void Renderer::Render(GLFWwindow* renderWindow) const
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	
	/*draw elements*/
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	/* Swap front and back buffers */
	glfwSwapBuffers(renderWindow);
}

void Renderer::SetBackgroundColor(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
}
