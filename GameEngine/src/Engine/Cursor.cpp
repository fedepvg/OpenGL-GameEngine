#include "Cursor.h"

#include "GLFW/glfw3.h"

#include "Window.h"

Cursor::Cursor(Window* activeWindow)
{
	window = activeWindow;
	glfwSetCursorPosCallback(window->getWindow(), Cursor::mouse_callback);
}

Cursor::~Cursor() 
{

}

void Cursor::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	xInput = xpos;
	yInput = ypos;
}


double Cursor::GetCursorX() 
{
	return xInput;
}

double Cursor::GetCursorY() 
{
	return yInput;
}

void Cursor::SetCursorMode(CursorMode newMode) 
{
	switch (newMode)
	{
	case Cursor::normal:
		glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		break;
	case Cursor::capture:
		glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		break;
	default:
		break;
	}
}