#include "BaseGame.h"

#include <iostream>

#include "GLFW/glfw3.h"
using namespace std;

BaseGame::BaseGame()
{
	/* Initialize the library */
	if (!glfwInit());
		//return -1;
	window.open(800, 600, "window");
	gameLoop();
}

BaseGame::~BaseGame()
{

}

int BaseGame::gameLoop()
{
	GLFWwindow* currentWindow = window.getWindow();
	while (!glfwWindowShouldClose(currentWindow))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(currentWindow);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
