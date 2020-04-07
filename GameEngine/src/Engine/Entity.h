#ifndef ENTITY_H
#define ENTITY_H
#define EXPORTDLL _declspec(dllexport)

#include "glm/glm.hpp"

#include "Renderer.h"

class Texture;

class EXPORTDLL Entity
{
public:
	Entity();
	Entity(glm::vec3 pos, Texture* tex);
	~Entity();
	//void SetShader();

	//transformations
	void Rotate(float angle, glm::vec3 axis);
	void Translate(float value, glm::vec3 axis);
	void Scale(glm::vec3 scaleValues);
	glm::vec2 GetPosition();
	glm::vec2 GetScale();
	void SetPosition(glm::vec2 newPosition);

	//Getters for buffers and pointers
	GLuint GetVertexArray();
	GLuint GetVertexBuffer();
	GLuint GetElementBuffer();
	Texture* GetTexturePointer();
	glm::mat4 GetModel();
	unsigned int GetShader();

protected:
	glm::vec3 position;
	glm::vec3 scale;
	glm::mat4 model;
	unsigned int uniModel;
	unsigned int programID;
	GLuint posAttrib;
	GLuint colAttrib;
	GLuint texAttrib;
	GLuint ebo;
	GLuint vbo;
	GLuint vertexArray;
	Texture* texture;
	//Deprecated System, now Renderer does de heavy lifting, not Entity
	//virtual void Render() = 0;
	//static Renderer* renderer;
};
#endif