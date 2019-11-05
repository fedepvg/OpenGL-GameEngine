#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "BaseGame.h"
#include "LoadShader.h"
#include <iostream>

//#include <list>

#include "Shape.h"
#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "Entity.h"

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
	Entity::renderer = renderer;
	entityList.clear();
	window->open(screenWidth, screenHeight, "window");
	input = new Input(window->getWindow());
	glewExperimental = GL_TRUE;
	glewInit();
}

BaseGame::~BaseGame()
{
	delete window;
	delete renderer;
}

int BaseGame::GameLoop()
{
	GLFWwindow* currentWindow = window->getWindow();
	Entity* actualShape= new Shape;
	entityList.push_front(actualShape);

	while (!glfwWindowShouldClose(currentWindow))
	{
		Update();
		//input processing
		if (input->GetKey(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(currentWindow, GL_TRUE);



		//use renderer		
		renderer->SetBackgroundColor(0.1f, 0.1f, 0.1f, 0.0f);
		renderer->Render(currentWindow, entityList);

		/* Poll for and process events */
		glfwPollEvents();
	}
	delete input;
	glfwTerminate();
	return 0;
}
