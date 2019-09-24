#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "BaseGame.h"
#include "LoadShader.h"
#include <iostream>
#include "Shape.h"
#include "Window.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

using namespace std;

BaseGame::BaseGame()
{
	/* Initialize the library */
	if (!glfwInit());
	//return -1;
	window = new Window();
	renderer = new Renderer();
	window->open(800, 600, "window");

	glewExperimental = GL_TRUE;
	glewInit();
	GameLoop();
}

BaseGame::~BaseGame()
{

}

int BaseGame::GameLoop()
{
	Shape shape;
	GLFWwindow* currentWindow = window->getWindow();

	renderer->SetShader();
	
	while (!glfwWindowShouldClose(currentWindow))
	{
		//input processing
		if (glfwGetKey(currentWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(currentWindow, GL_TRUE);

		//scaling
		if (glfwGetKey(currentWindow, GLFW_KEY_H) == GLFW_PRESS)
		{
			renderer->Scale({ 1.1f,1.1f,1.1f });
		}

		if (glfwGetKey(currentWindow, GLFW_KEY_K) == GLFW_PRESS)
		{
			renderer->Scale({ 0.9f,0.9f,0.9f });
		}

		//rotating
		if (glfwGetKey(currentWindow, GLFW_KEY_E) == GLFW_PRESS)
		{
			renderer->Rotate(-1.0f, { 0.0f,0.0f,1.f });
		}

		if (glfwGetKey(currentWindow, GLFW_KEY_F) == GLFW_PRESS)
		{
			renderer->Rotate(-1.0f, { 0.0f,1.0f,0.f });
		}

		else if (glfwGetKey(currentWindow, GLFW_KEY_Q) == GLFW_PRESS)
		{
			renderer->Rotate(1.0f, { 0.0f,0.0f,1.f });
		}

		//translating
		if (glfwGetKey(currentWindow, GLFW_KEY_A) == GLFW_PRESS)
		{
			renderer->Translate(-0.03f, {1.0f,0.0f,0.0f});
		}

		if (glfwGetKey(currentWindow, GLFW_KEY_D) == GLFW_PRESS)
		{
			renderer->Translate(0.03f, { 1.0f,0.0f,0.0f });
		}

		if (glfwGetKey(currentWindow, GLFW_KEY_W) == GLFW_PRESS)
		{
			renderer->Translate(0.03f, { 0.0f,1.0f,0.0f });
		}
		if (glfwGetKey(currentWindow, GLFW_KEY_S) == GLFW_PRESS)
		{
			renderer->Translate(-0.03f, { 0.0f,1.0f,0.0f });
		}

		

		//use renderer
		renderer->SetBackgroundColor(0.1f, 0.1f, 0.1f, 0.0f);

		renderer->Render(currentWindow);

		/* Poll for and process events */
		glfwPollEvents();
	}
	//glDeleteProgram(programID);
	glfwTerminate();
	return 0;
}
