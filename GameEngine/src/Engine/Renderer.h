#ifndef RENDERER_H
#define RENDERER_H
#define EXPORTDLL _declspec(dllexport)

#include <list>

#include "Window.h"
#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

class Entity;

class EXPORTDLL Renderer
{
private:
	unsigned int uniModel;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
	GLuint programID;
public:
	Renderer();
	~Renderer();
	void Render(GLFWwindow* renderWindow, std::list<Entity*> objectList);// const;
	void SetBackgroundColor(float r, float g, float b, float a) const; 
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix();
};

#endif // !RENDERER_H