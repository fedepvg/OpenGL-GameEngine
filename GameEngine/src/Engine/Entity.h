#ifndef ENTITY_H
#define ENTITY_H
#define EXPORTDLL _declspec(dllexport)

#include "glm/glm.hpp"

#include "Renderer.h"

class EXPORTDLL Entity
{
protected:
	glm::vec3 position;
	glm::mat4 model;
	unsigned int uniModel;
	unsigned int programID;
	GLuint posAttrib;
	GLuint colAttrib;
	GLuint texAttrib;
	GLuint ebo;
	GLuint vbo;
	GLuint vertexArray;
public:
	Entity();
	Entity(glm::vec3 pos);
	void SetShader();
	void Rotate(float angle, glm::vec3 axis);
	void Translate(float value, glm::vec3 axis);
	void Scale(glm::vec3 scaleValues);
	glm::vec2 GetPosition();
	virtual void Render();
	static Renderer* renderer;
};
#endif