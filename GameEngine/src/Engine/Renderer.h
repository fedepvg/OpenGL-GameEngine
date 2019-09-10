#ifndef RENDERER_H
#define RENDERER_H
#define EXPORTDLL _declspec(dllexport)

#include "Window.h"
#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

class EXPORTDLL Renderer
{
private:
	unsigned int uniModel;
	glm::mat4 myMatrix;
	GLuint programID;
public:
	Renderer();
	~Renderer();
	void Render(GLFWwindow* renderWindow);// const;
	void SetBackgroundColor(float r, float g, float b, float a) const;
	void SetShader();
};

#endif // !RENDERER_H