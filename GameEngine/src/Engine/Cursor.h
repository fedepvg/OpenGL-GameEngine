#ifndef CURSOR_H
#define CURSOR_H

#define EXPORTDLL _declspec(dllexport)

#include "Window.h"

class EXPORTDLL Cursor
{
public:
	Cursor(Window* activeWindow);
	~Cursor();
	double GetCursorX();
	double GetCursorY();
	enum CursorMode
	{
		normal, capture
	};
	void SetCursorMode(CursorMode newMode);

private:
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static double xInput;
	static double yInput;
	Window* window;
};
#endif