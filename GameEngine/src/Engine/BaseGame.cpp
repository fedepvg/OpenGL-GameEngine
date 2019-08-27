#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "BaseGame.h"
#include "LoadShader.h"
#include <iostream>

using namespace std;

BaseGame::BaseGame()
{
	/* Initialize the library */
	if (!glfwInit());
	//return -1;
	window.open(800, 600, "window");

	glewExperimental = GL_TRUE;
	glewInit();



	GameLoop();
}

BaseGame::~BaseGame()
{

}

int BaseGame::GameLoop()
{
	GLFWwindow* currentWindow = window.getWindow();

	//load shaders
	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	static const GLfloat g_vertex_buffer_data[] = {
	   0.7f, -0.7f, 0.0f, 1.0f, 1.0f, 0.0f, //+-
	   -0.7f, 0.7f, 0.0f, 1.0f, 1.0f, 0.0f, //-+
	   -0.7f, -0.7f, 0.0f, 1.0f, 0.0f, 0.0f, //--
	   0.7f,  0.7f, 0.0f, 1.0f, 0.0f, 1.0f, //++  
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


	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(programID, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	GLint colAttrib = glGetAttribLocation(programID, "customColor");
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(colAttrib);

	//use shader
	glUseProgram(programID);

	while (!glfwWindowShouldClose(currentWindow))
	{
		if (glfwGetKey(currentWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(currentWindow, GL_TRUE);

		//use renderer
		//renderer.SetBackgroundColor(1.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//renderer.Render(currentWindow); - when renderer works, uncomment this
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window.getWindow());
		/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteProgram(programID);
	glfwTerminate();
	return 0;
}
