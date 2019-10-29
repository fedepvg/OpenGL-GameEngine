#include "Game.h"
#include "Engine/BaseGame.h"
#include "Engine/Shape.h"

#include <iostream>

Game::Game(int width, int height) : BaseGame(width, height)
{

}

Game::~Game()
{

}

void Game::Init()
{
	GameLoop();
}

void Game::Update()
{	
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
		shape.Translate(-0.03f, { 1.0f,0.0f,0.0f });
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
}