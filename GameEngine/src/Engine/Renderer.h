#ifndef RENDERER_H
#define RENDERER_H
#define EXPORTDLL _declspec(dllexport)

#include <list>

#include "Window.h"
#include "Entity.h"
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
	void Render(GLFWwindow* renderWindow, std::list<Entity*> objectList);// const;
	void SetBackgroundColor(float r, float g, float b, float a) const;
	void SetShader();
	/*void Rotate(float angle, glm::vec3 axis);
	void Translate(float value, glm::vec3 axis);
	void Scale(glm::vec3 scaleValues);*/
};

#endif // !RENDERER_H