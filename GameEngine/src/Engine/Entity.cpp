#include "Entity.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include"glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

#include "LoadShader.h"
#include "Texture.h"
#include "Renderer.h"
#include "BaseGame.h"

Entity::Entity()
{
	position = { 0, 0, 0 };
	BaseGame::entityList.push_front(this);
}

Renderer* Entity::renderer = nullptr;

Entity::Entity(glm::vec3 pos)
{
	position = pos;
	BaseGame::entityList.push_front(this);
}

void Entity::SetShader()
{
	//load shaders
	programID = LoadShaders("../src/Engine/SimpleVertexShader.vertexshader", "../src/Engine/SimpleFragmentShader.fragmentshader");
	Texture tex("../res/BOKEE.png");

	//use shader
	glUseProgram(programID);

	// Specify the layout of the vertex data
	posAttrib = glGetAttribLocation(programID, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	colAttrib = glGetAttribLocation(programID, "customColor");
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(colAttrib);

	texAttrib = glGetAttribLocation(programID, "aTexCoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	model = glm::mat4(1.0f);
	uniModel = glGetUniformLocation(programID, "model");
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

	glm::mat4 view = glm::lookAt(
		glm::vec3(0.f, 0.f, 1.5f), // position
		glm::vec3(0.0f, 0.0f, 0.0f), // look at
		glm::vec3(0.0f, 1.0f, 0.0f)  // up
	);
	GLint uniView = glGetUniformLocation(programID, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 proj = glm::ortho(-1.f, 1.f, -1.f, 1.f, 0.f, 100.f);
	GLint uniProj = glGetUniformLocation(programID, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	glUniform1i(glGetUniformLocation(programID, "tex"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex.GetTexture());
}

void Entity::Rotate(float angle, glm::vec3 axis)
{
	model = glm::rotate(model, glm::radians(angle), axis);
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
}

void Entity::Scale(glm::vec3 scaleValues)
{
	model = glm::scale(model, scaleValues);
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
}

void Entity::Translate(float value, glm::vec3 axis)
{
	model = glm::translate(model, value * axis);
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
}

void Entity::Render() 
{
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
