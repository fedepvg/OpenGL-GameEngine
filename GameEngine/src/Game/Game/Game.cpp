#include "Game.h"
#include "Engine/BaseGame.h"
#include "Engine/Texture.h"
#include "Engine/Shader.h"
#include "Engine/DirectionalLight.h"

#include <iostream>

#include "FirstPersonCameraController.h"

Game::Game(int width, int height) : BaseGame(width, height)
{

}

Game::~Game()
{
	delete cursor;
	delete ourShader;
	delete testModel;
	delete dirLight;
}

void Game::Init()
{
	ourShader = new Shader("../src/Engine/3DVertexShader.vertexshader", "../src/Engine/3DFragmentShader.fragmentshader");

	fpsCamera = new FirstPersonCameraController(renderCamera, cursor);
	fpsCamera->SetSensitivity(0.3f);
	//shader initialization
	ourShader->SetVec3("viewPosition", renderCamera->GetPosition());
	ourShader->SetVec3("viewDirection", renderCamera->GetDirection());

	dirLight = new DirectionalLight(glm::vec3 { 0.f,0.5f,-1.f }, glm::vec3{ 0.1f,0.1f,0.1f },
		glm::vec3{ 1.0f,1.0f,1.0f }, glm::vec3{ 1.f,1.f,1.f });
	
	testModel = new Model("../res/model/backpack.obj", ourShader);
	GameLoop();
}

void Game::Update(const float deltaTime)
{
	ourShader->PassDirectionalLightValues(dirLight);
	
	if (cursor->GetCursorMode() != Cursor::CursorMode::capture)
		cursor->SetCursorMode(Cursor::CursorMode::capture);

	if (input->GetKey(GLFW_KEY_X))
	{
		renderCamera->RotatePitch(10.f);
	}
	

	//camera

	if (input->GetKey(GLFW_KEY_A))
	{
		fpsCamera->TranslateX(-10.f);
	}

	if (input->GetKey(GLFW_KEY_D))
	{
		fpsCamera->TranslateX(10.f);
	}

	if (input->GetKey(GLFW_KEY_W))
	{
		fpsCamera->TranslateY(10.f);
	}
	if (input->GetKey(GLFW_KEY_S))
	{
		fpsCamera->TranslateY(-10.f);
	}

	if (input->GetKey(GLFW_KEY_RIGHT))
	{
		testModel->Rotate(100.f * deltaTime, glm::vec3(0.f,1.f,0));
	}

	if (input->GetKey(GLFW_KEY_LEFT))
	{
		testModel->Rotate(100.f * deltaTime, glm::vec3(0.f,-1.f,0));
	}

	fpsCamera->Update();
	
	renderCamera->Update();
	ourShader->SetVec3("viewPosition", renderCamera->GetPosition());
	//ourShader->SetVec3("viewDirection", renderCamera->GetDirection());
	
	testModel->Draw();
}