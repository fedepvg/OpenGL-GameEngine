#include "Game.h"
#include "Engine/BaseGame.h"
#include "Engine/Texture.h"
#include "Engine/Shader.h"
#include "Engine/DirectionalLight.h"
#include "Engine/PointLight.h"
#include "Engine/SpotLight.h"
#include "Engine/BoundingBox.h"
#include "Engine/Renderer3D.h"

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
	ourShader->SetVec3("viewPosition", renderCamera->GetPosition());
	ourShader->SetVec3("viewDirection", renderCamera->GetDirection());

	dirLight = new DirectionalLight(glm::vec3{ 0.f,0.5f,-1.f }, glm::vec3{ 0.1f,0.1f,0.1f },
		glm::vec3{ 0.3f,0.3f,0.3f }, glm::vec3{ 1.f,1.,1.f });

	pointLightList.push_front(new PointLight(glm::vec3{ 10.f,0.f,0.f }, glm::vec3{ 0.1f,0.0f,0.0f },
		glm::vec3{ 0.4f,0.0f,0.0f }, glm::vec3{ 0.4f,0.0f,0.0f },
		1.f, 0.007f, 0.0002f));

	spotLightList.push_front(new SpotLight(glm::vec3{ 0.f, 0.f, 100.f }, glm::vec3{ 0.f, 0.f, 1.f }, 12.5f, 17.5,
		glm::vec3{ 0.f, 0.f, 0.2f }, glm::vec3{ 0.f, 0.f, 0.6f }, glm::vec3{ 0.0f, 0.0f, 0.6f },
		1.f, 0.14f, 0.07f));

	testModel = new Model("../res/model/backpack.obj", ourShader);
	testModel2 = new Model("../res/model/backpack.obj", ourShader);
	testModel3 = new Model("../res/model/backpack.obj", ourShader);
	testModel4 = new Model("../res/model/backpack.obj", ourShader);
	bsp = new Model("../res/BSPModel/Planes.fbx", ourShader, false);

	testModel2->Translate(20, { -1,0,0 });
	testModel3->Translate(20, { 1,0,0 });
	testModel4->Translate(20, { 0,0,-1 });
	//bsp->SetParent(testModel);
	ourShader->SetVec3("viewPosition", renderCamera->GetPosition());
	GameLoop();
}

void Game::Update(const float deltaTime)
{
	if (cursor->GetCursorMode() != Cursor::CursorMode::capture)
		cursor->SetCursorMode(Cursor::CursorMode::capture);

	/*if (input->GetKey(GLFW_KEY_X))
	{
		renderCamera->RotatePitch(10.f);
	}*/

	if (input->GetKey(GLFW_KEY_3))
	{
		Renderer3D::SetBspEnabled(true);
	}

	if (input->GetKey(GLFW_KEY_4))
	{
		Renderer3D::SetFrustumCullingEnabled(true);
	}

	if (input->GetKey(GLFW_KEY_5))
	{
		Renderer3D::SetBspEnabled(false);
	}

	if (input->GetKey(GLFW_KEY_6))
	{
		Renderer3D::SetFrustumCullingEnabled(false);
	}

	
	//camera

	if (input->GetKey(GLFW_KEY_A))
	{
		fpsCamera->TranslateX(-50.f * deltaTime);
	}

	if (input->GetKey(GLFW_KEY_D))
	{
		fpsCamera->TranslateX(50.f * deltaTime);
	}

	if (input->GetKey(GLFW_KEY_W))
	{
		fpsCamera->TranslateY(50.f * deltaTime);
	}
	if (input->GetKey(GLFW_KEY_S))
	{
		fpsCamera->TranslateY(-50.f * deltaTime);
	}

	if (input->GetKey(GLFW_KEY_RIGHT))
	{
		testModel->Translate(50.f * deltaTime, glm::vec3(1.f, 0.f, 0));
	}

	if (input->GetKey(GLFW_KEY_LEFT))
	{
		testModel->Translate(50.f * deltaTime, glm::vec3(-1.f, 0.f, 0));
	}

	if (input->GetKey(GLFW_KEY_UP))
	{
		bsp->Scale(glm::vec3(1.1f));
	}
	
	if (input->GetKey(GLFW_KEY_DOWN))
	{
		bsp->Scale(glm::vec3(.9f));
	}

	if (input->GetKey(GLFW_KEY_V))
	{
		testModel->Rotate(40.f * deltaTime, glm::vec3(0.f, 1.f, 0));
	}

	if (input->GetKey(GLFW_KEY_X))
	{
		testModel->Translate(-40.f * deltaTime, glm::vec3(1.f, 0.f, 0));
	}

	if (input->GetKey(GLFW_KEY_C))
	{
		testModel->Translate(40.f * deltaTime, glm::vec3(1.f, 0.f, 0));
	}
	
	if (input->GetKey(GLFW_KEY_B))
	{
		testModel->Rotate(-40.f * deltaTime, glm::vec3(0.f, 1.f, 0));
	}

	if (input->GetKey(GLFW_KEY_H))
	{
		testModel->GetNode("Cube.037__0")->Scale(glm::vec3(.9f));
	}

	if (input->GetKey(GLFW_KEY_J))
	{
		testModel->GetNode("Cube.037__0")->Scale(glm::vec3(1.1f));
	}

	if (input->GetKey(GLFW_KEY_Y))
	{
		testModel->GetNode("Cylinder.049__0")->Translate(25.f * deltaTime, glm::vec3(-1.f, 0.f, 0));
	}

	if (input->GetKey(GLFW_KEY_U))
	{
		testModel->GetNode("Cylinder.049__0")->Translate(-25.f * deltaTime, glm::vec3(-1.f, 0.f, 0));
	}

	if (input->GetKey(GLFW_KEY_I))
	{
		testModel->GetNode("Cylinder.049__0")->Rotate(50.f * deltaTime, glm::vec3(0.f, 1.f, 0));
	}

	if (input->GetKey(GLFW_KEY_O))
	{
		testModel->GetNode("Cylinder.049__0")->Rotate(-50.f * deltaTime, glm::vec3(0.f, 1.f, 0));
	}

	if (input->GetKey(GLFW_KEY_SPACE))
	{
		bsp->SetParent(testModel->GetNode("Cube.037__0"));
	}

	if (input->GetKey(GLFW_KEY_ENTER))
	{
		bsp->SetParent(nullptr);
	}
	if (input->GetKey(GLFW_KEY_1))
	{
		testModel->SetColliderVisibility(true);
		bsp->SetColliderVisibility(true);
	}
	if (input->GetKey(GLFW_KEY_2))
	{
		testModel->SetColliderVisibility(false);
		bsp->SetColliderVisibility(false);
	}

	fpsCamera->Update();

	renderCamera->Update();

	ourShader->PassDirectionalLightValues(dirLight);

	ourShader->PassPointLightListValues(pointLightList);
	ourShader->SetInt("activePointLights", pointLightList.size());

	std::list<SpotLight*>::iterator it = spotLightList.begin();
	(*it)->position = renderCamera->GetPosition();
	(*it)->direction = renderCamera->GetDirection();

	ourShader->PassSpotLightListValues(spotLightList);
	ourShader->SetInt("activeSpotLights", spotLightList.size());

	ourShader->SetVec3("viewPosition", renderCamera->GetPosition());
}