#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "BaseGame.h"
#include "LoadShader.h"
#include <iostream>

#include "Shape.h"
#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "Entity.h"
#include "CollisionManager.h"

#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "AssimpImporter.h"
#include "Renderer3D.h"

using namespace std;

list<Entity*> BaseGame::entityList;

BaseGame::BaseGame(int screenWidth, int screenHeight)
{
	/* Initialize the library */
	if (!glfwInit())
		glfwTerminate();
	window = new Window();
	entityList.clear();
	window->open(screenWidth, screenHeight, "window");
	collisionManager = new CollisionManager();
	input = new Input(window->getWindow());
	glewExperimental = GL_TRUE;
	glewInit();
	//renderer = new Renderer(window);
	renderer3d = new Renderer3D(window);
	//Entity::renderer = renderer;
	//Entity::programID = renderer->GetShader();
	lastFrameTime = 0.f;
	//renderCamera = renderer->GetCamera();
	renderCamera = renderer3d->GetCamera();
	sceneRoot = new Entity3D;
	Entity3D::SetSceneRoot(sceneRoot);
}

BaseGame::~BaseGame()
{
	delete window;
	//delete renderer;
	delete renderer3d;
	//delete cursor;
	delete sceneRoot;
}

int BaseGame::GameLoop()
{
	GLFWwindow* currentWindow = window->getWindow();

	AssimpImporter aImporter;

	cursor = new Cursor(window);

	while (!glfwWindowShouldClose(currentWindow))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		//use renderer		
		//renderer->SetBackgroundColor(0.1f, 0.1f, 0.5f, 0.0f);
		//renderer3d->SetBackgroundColor(0.1f, 0.1f, 0.5f, 0.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		Update(deltaTime);
		//input processing
		if (input->GetKey(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(currentWindow, GL_TRUE);

		//update camera
		renderCamera->Update();

		//renderer->Render(entityList);
		renderer3d->Draw(sceneRoot);

		/* Poll for and process events */
		glfwPollEvents();
	}
	delete input;
	/*if(cursor != nullptr)
		delete cursor;*/
	glfwTerminate();
	return 0;
}
