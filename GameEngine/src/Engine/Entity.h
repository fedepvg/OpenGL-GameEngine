#ifndef ENTITY_H
#define ENTITY_H
#define EXPORTDLL _declspec(dllexport)

#include "glm/glm.hpp"

class Renderer;

class EXPORTDLL Entity
{
protected:
	glm::vec3 position;
	glm::mat4 model;
	unsigned int uniModel;
	unsigned int programID;
public:
	Entity();
	Entity(glm::vec3 pos);
	void SetShader();
	void Rotate(float angle, glm::vec3 axis);
	void Translate(float value, glm::vec3 axis);
	void Scale(glm::vec3 scaleValues);
	virtual void Render();
	static Renderer* renderer;
};
#endif