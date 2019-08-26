#include "BaseGame.h"
#include <iostream>
#include "GLFW/glfw3.h"
#include "GL/glew.h"
using namespace std;

BaseGame::BaseGame()
{
	/* Initialize the library */
	if (!glfwInit());
		//return -1;
	window.open(800, 600, "window");
	GameLoop();
}

BaseGame::~BaseGame()
{

}

int BaseGame::GameLoop()
{
	GLFWwindow* currentWindow = window.getWindow();
	while (!glfwWindowShouldClose(currentWindow))
	{
		//use renderer
		renderer.SetBackgroundColor(1.0f, 0.0f, 0.0f, 0.0f);
		renderer.Render(currentWindow);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
