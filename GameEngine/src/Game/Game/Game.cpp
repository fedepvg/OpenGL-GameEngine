#include "Game.h"
#include "Engine/BaseGame.h"
#include "Engine/Shape.h"
#include "Engine/Texture.h"

#include <iostream>

Game::Game(int width, int height) : BaseGame(width, height)
{

}

Game::~Game()
{
	delete shape;
	//delete shape2;
}

void Game::Init()
{
	Texture bokeTex("../res/BOKEE.png");
	Texture comuTex("../res/texture.png");

	shape = new Shape({ 0,0,0 }, {1,1,0}, &bokeTex);
	shape2 = new Shape({ 0,0,0 }, {1,1,0 }, &comuTex);
	GameLoop();
}

void Game::Update()
{	
	std::cout<<shape2->GetPosition().x<<" , "<< shape2->GetPosition().y<<std::endl<< std::endl;

	//Texture tex("../res/BOKEE.png");

	//scaling
	if (input->GetKey(GLFW_KEY_H))
	{
		shape->Scale({ 1.1f,1.1f,1.1f });
	}

	if (input->GetKey(GLFW_KEY_K))
	{
		shape->Scale({ 0.9f,0.9f,0.9f });
	}

	//rotating
	if (input->GetKey(GLFW_KEY_E))
	{
		shape->Rotate(-1.0f, { 0.0f,0.0f,1.f });
	}

	if (input->GetKey(GLFW_KEY_F))
	{
		shape->Rotate(-1.0f, { 0.0f,1.0f,0.f });
	}

	else if (input->GetKey(GLFW_KEY_Q))
	{
		shape->Rotate(1.0f, { 0.0f,0.0f,1.f });
	}

	//translating
	if (input->GetKey(GLFW_KEY_A))
	{
		shape2->Translate(-0.03f, { 1.0f,0.0f,0.0f });
	}

	if (input->GetKey(GLFW_KEY_D))
	{
		shape2->Translate(0.03f, { 1.0f,0.0f,0.0f });
	}

	if (input->GetKey(GLFW_KEY_W))
	{
		shape2->Translate(0.03f, { 0.0f,1.0f,0.0f });
	}
	if (input->GetKey(GLFW_KEY_S))
	{
		shape2->Translate(-0.03f, { 0.0f,1.0f,0.0f });
	}
}