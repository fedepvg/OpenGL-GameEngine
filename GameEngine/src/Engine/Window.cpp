#include "Window.h"

#include "GLFW/glfw3.h"


void Window::open(int width, int height, const char* title)
{
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
}

GLFWwindow* Window::getWindow()
{
	return window;
}