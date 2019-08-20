#ifndef WINDOW_H
#define	WINDOW_H
#define EXPORTDLL _declspec(dllexport)

#include "../libs/glfw-3.3/include/GLFW/glfw3.h"
//#include "GLFW/glfw3.h"

class EXPORTDLL Window 
{
public:
	void open(int width, int height, const char* title);
	GLFWwindow* getWindow();
private:
	GLFWwindow* window;
};

#endif // !WINDOW_H
