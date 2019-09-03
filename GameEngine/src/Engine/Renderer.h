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
	void SetBackgroundColor(float r, float g, float b, float a) const;
	void SetShader();
};

#endif // !RENDERER_H