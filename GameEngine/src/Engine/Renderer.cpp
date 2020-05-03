#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "LoadShader.h"

#include "Renderer.h"
#include "Texture.h"
#include "Entity.h"

#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

Renderer::Renderer(Window* window)
{
	renderWindow = window->getWindow();

	renderCamera = new Camera({ 0.f,0.f,500.f }, { 0.f,1.f,0.f }, {0.f,0.f,-1.f},-90.f,0.f);
	programID = NULL;

	//projMatrix = glm::ortho(-window->GetWidth()/2, window->GetWidth() / 2, -window->GetHeight() / 2, window->GetHeight() / 2, 0.f, 100.f);
	projMatrix = glm::perspective(45.0f, window->GetWidth()/ window->GetHeight(), 0.f, 100.f);

	//viewMatrix = glm::rotate(viewMatrix, glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
	//model = glm::rotate(model, glm::radians(angle), axis);

	SetShader();
}

Renderer::~Renderer()
{
	if (programID != NULL) 
	{
		glDeleteProgram(programID);
	}

	delete renderCamera;
}

void Renderer::Render(std::list<Entity*> objectList)// const
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	/*draw elements*/
	for (std::list<Entity*>::iterator it = objectList.begin(); it != objectList.end(); it++)
	{
		RenderEntity(*it);
	}

	/* Swap front and back buffers */
	glfwSwapBuffers(renderWindow);
}

void Renderer::SetBackgroundColor(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
}

glm::mat4 Renderer::GetProjMatrix()
{
	return projMatrix;
}

GLuint Renderer::GetShader() 
{
	return programID;
}

Camera* Renderer::GetCamera() 
{
	return renderCamera;
}

void Renderer::SetShader()
{
	//load shaders
	programID = LoadShaders("../src/Engine/SimpleVertexShader.vertexshader", "../src/Engine/SimpleFragmentShader.fragmentshader");

	//use shader
	glUseProgram(programID);

	GLint uniProj = glGetUniformLocation(programID, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(projMatrix));

	glUniform1i(glGetUniformLocation(programID, "aTexCoord"), 0);

	uniModel = glGetUniformLocation(programID, "model");
	uniView = glGetUniformLocation(programID, "view");

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::RenderEntity(Entity* entityToRender) 
{
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(renderCamera->GetViewMatrix()));
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(entityToRender->GetModel()));
	glUseProgram(programID);
	glBindVertexArray(entityToRender->GetVertexArray());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, entityToRender->GetTexturePointer()->GetTexture());

	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
}