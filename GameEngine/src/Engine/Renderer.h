#ifndef RENDERER_H
#define RENDERER_H
#define EXPORTDLL _declspec(dllexport)
#include "Window.h"

class EXPORTDLL Renderer
{
public:
	Renderer();
	~Renderer();
	void Render(GLFWwindow* renderWindow) const;
};

#endif // !RENDERER_H