#ifndef WINDOW_H
#define	WINDOW_H
#define EXPORTDLL _declspec(dllexport)

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class EXPORTDLL Window 
{
public:
	void open(int width, int height, const char* title);
	GLFWwindow* getWindow();
private:
	GLFWwindow* window;
};

#endif // !WINDOW_H
