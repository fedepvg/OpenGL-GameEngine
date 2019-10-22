#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "BaseGame.h"
#include "LoadShader.h"
#include <iostream>
#include "Shape.h"
#include "Window.h"
#include "Renderer.h"
#include "Input.h"

#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

using namespace std;

BaseGame::BaseGame(int screenWidth, int screenHeight)
{
	/* Initialize the library */
	if (!glfwInit())
		glfwTerminate();
	window = new Window();
	renderer = new Renderer();
	window->open(screenWidth, screenHeight, "window");

	glewExperimental = GL_TRUE;
	glewInit();
	GameLoop();
}

BaseGame::~BaseGame()
{
	delete window;
	delete renderer;
}

int BaseGame::GameLoop()
{
	Shape shape;
	GLFWwindow* currentWindow = window->getWindow();
	input = new Input(currentWindow);

	//renderer->SetShader();
	
	while (!glfwWindowShouldClose(currentWindow))
	{
		//input processing
		if (input->GetKey(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(currentWindow, GL_TRUE);

		//scaling
		if (input->GetKey(GLFW_KEY_H))
		{
			shape.Scale({ 1.1f,1.1f,1.1f });
		}

		if (input->GetKey(GLFW_KEY_K))
		{
			shape.Scale({ 0.9f,0.9f,0.9f });
		}

		//rotating
		if (input->GetKey(GLFW_KEY_E))
		{
			shape.Rotate(-1.0f, { 0.0f,0.0f,1.f });
		}

		if (input->GetKey(GLFW_KEY_F))
		{
			shape.Rotate(-1.0f, { 0.0f,1.0f,0.f });
		}

		else if (input->GetKey(GLFW_KEY_Q))
		{
			shape.Rotate(1.0f, { 0.0f,0.0f,1.f });
		}

		//translating
		if (input->GetKey(GLFW_KEY_A))
		{
			shape.Translate(-0.03f, {1.0f,0.0f,0.0f});
		}

		if (input->GetKey(GLFW_KEY_D))
		{
			shape.Translate(0.03f, { 1.0f,0.0f,0.0f });
		}

		if (input->GetKey(GLFW_KEY_W))
		{
			shape.Translate(0.03f, { 0.0f,1.0f,0.0f });
		}
		if (input->GetKey(GLFW_KEY_S))
		{
			shape.Translate(-0.03f, { 0.0f,1.0f,0.0f });
		}

		//use renderer
		renderer->SetBackgroundColor(0.1f, 0.1f, 0.1f, 0.0f);

		renderer->Render(currentWindow);

		/* Poll for and process events */
		glfwPollEvents();
	}
	//glDeleteProgram(programID);
	delete input;
	glfwTerminate();
	return 0;
}
