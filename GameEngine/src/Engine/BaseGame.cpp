#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "BaseGame.h"
#include <iostream>

using namespace std;

const GLchar* vertexSource = R"glsl(
    #version 150 core

    in vec2 position;

    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";

const GLchar* fragmentSource = R"glsl(
    #version 150 core

    out vec4 outColor;

    void main()
    {
        outColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
)glsl";


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

	GLfloat vertices[] =
	{
		-0.5f,  0.5f,	// Top-left
		 0.5f,  0.5f,	// Top-right
		 0.5f, -0.5f,	// Bottom-right
		-0.5f, -0.5f,	// Bottom-left
	};

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint elements[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	// Create an element array
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Link the vertex and fragment shader into a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//glBindFragDataLocation(shaderProgram, 0, "outColor"); // no hace falta al ser 1 solo framebuffer
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

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

	glfwTerminate();
	return 0;
}
