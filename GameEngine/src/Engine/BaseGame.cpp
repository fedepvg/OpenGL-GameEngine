#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "BaseGame.h"
#include "LoadShader.h"
#include <iostream>
#include "Shape.h"
#include "Window.h"
#include "Renderer.h"

using namespace std;

BaseGame::BaseGame()
{
	/* Initialize the library */
	if (!glfwInit());
	//return -1;
	window = new Window();
	renderer = new Renderer();
	window->open(800, 600, "window");

	glewExperimental = GL_TRUE;
	glewInit();
	GameLoop();
}

BaseGame::~BaseGame()
{

}

int BaseGame::GameLoop()
{
	Shape shape;
	GLFWwindow* currentWindow = window->getWindow();

	renderer->SetShader();
	
	while (!glfwWindowShouldClose(currentWindow))
	{

		if (glfwGetKey(currentWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(currentWindow, GL_TRUE);

		//use renderer
		renderer->SetBackgroundColor(0.1f, 0.1f, 0.1f, 0.0f);

		renderer->Render(currentWindow);

		/* Poll for and process events */
		glfwPollEvents();
	}
	//glDeleteProgram(programID);
	glfwTerminate();
	return 0;
}
