#include "Cursor.h"

#include "GLFW/glfw3.h"

#include "Window.h"

Cursor* Cursor::activeCursor = nullptr;
double Cursor::xInput = 0.0;
double Cursor::yInput = 0.0;

Cursor::Cursor(Window* activeWindow)
{
	if (activeCursor == nullptr)
	{
		activeCursor = this;
	}
	else
	{
		delete this;
	}
	window = activeWindow;
	glfwSetCursorPosCallback(window->getWindow(), Cursor::mouse_callback);
	glfwSetCursorPos(window->getWindow(), 0, 0);
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
	currentMode = newMode;
}

Cursor::CursorMode Cursor::GetCursorMode()
{
	return currentMode;
}