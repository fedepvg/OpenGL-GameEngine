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

	viewMatrix = glm::lookAt(
		glm::vec3(0.f, 0.f, 1.5f), // position
		glm::vec3(0.0f, 0.0f, 0.0f), // look at
		glm::vec3(0.0f, 1.0f, 0.0f)  // up
	);

	//projMatrix = glm::ortho(0.f,800.f,0.f, 600.f, 0.f, 100.f);
	projMatrix = glm::ortho(-window->GetWidth()/2, window->GetWidth() / 2, -window->GetHeight() / 2, window->GetHeight() / 2, 0.f, 100.f);
	//projMatrix = glm::perspective(45.0f, window->GetWidth()/ window->GetHeight(), 0.f, 100.f);
	//projMatrix = glm::perspectiveFov(45.0f, window->GetWidth(), window->GetHeight(), 0.f, 100.f);
}

Renderer::~Renderer()
{

}

void Renderer::Render(std::list<Entity*> objectList)// const
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	/*draw elements*/
	for (std::list<Entity*>::iterator it = objectList.begin(); it != objectList.end(); it++)
	{
		(*it)->Render();
	}

	/* Swap front and back buffers */
	glfwSwapBuffers(renderWindow);
}

void Renderer::SetBackgroundColor(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
}

glm::mat4 Renderer::GetViewMatrix()
{
	return viewMatrix;
}

glm::mat4 Renderer::GetProjMatrix()
{
	return projMatrix;
}