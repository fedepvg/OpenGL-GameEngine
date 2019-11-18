#include "Game.h"
#include "Engine/BaseGame.h"
#include "Engine/Texture.h"

#include <iostream>

Game::Game(int width, int height) : BaseGame(width, height)
{

}

Game::~Game()
{
	delete shape;
	delete shape2;
	delete anim;
}

void Game::Init()
{
	Texture bokeTex("../res/BOKEE.png");
	Texture comuTex("../res/texture.png");
	Texture animTex("../res/anim.png");

	shape = new Shape({ 0,0,0 }, {100,100,0}, &bokeTex);
	shape2 = new Shape({ 0,0,0 }, {100,100,0 }, &comuTex);
	anim = new Sprite({ 0,0,0 }, { 368, 200, 0 }, &animTex);
	anim->CreateAnimation(368, 368 / 8, 4, 0, 8);
	GameLoop();
}

void Game::Update(const float deltaTime)
{
	//scaling
	anim->UpdateCurrentAnimation(deltaTime);

	if (input->GetKey(GLFW_KEY_H))
	{
		anim->Scale({ 1.1f,1.1f,1.1f });
	}

	if (input->GetKey(GLFW_KEY_K))
	{
		anim->Scale({ 0.9f,0.9f,0.9f });
	}

	if (input->GetKey(GLFW_KEY_N))
	{
		shape2->Scale({ 1.1f,1.1f,1.1f });
	}

	if (input->GetKey(GLFW_KEY_M))
	{
		shape2->Scale({ 0.9f,0.9f,0.9f });
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
		shape2->Translate(-60.f, { 1.0f,0.0f,0.0f });
	}

	if (input->GetKey(GLFW_KEY_D))
	{
		shape2->Translate(60.f, { 1.0f,0.0f,0.0f });
	}

	if (input->GetKey(GLFW_KEY_W))
	{
		shape2->Translate(60.f, { 0.0f,1.0f,0.0f });
	}
	if (input->GetKey(GLFW_KEY_S))
	{
		shape2->Translate(-60.f, { 0.0f,1.0f,0.0f });
	}

	if (input->GetKey(GLFW_KEY_LEFT))
	{
		anim->Translate(-60.f, { 1.0f,0.0f,0.0f });
	}

	if (input->GetKey(GLFW_KEY_RIGHT))
	{
		anim->Translate(60.f, { 1.0f,0.0f,0.0f });
	}

	if (input->GetKey(GLFW_KEY_UP))
	{
		anim->Translate(60.f, { 0.0f,1.0f,0.0f });
	}
	if (input->GetKey(GLFW_KEY_DOWN))
	{
		anim->Translate(-60.f, { 0.0f,1.0f,0.0f });
	}

	//collisions

	if (collisionManager->CheckCollision(*anim, *shape2))
	{
		std::cout << "SI" << std::endl;
	}
	else
	{
		std::cout << "NO" << std::endl;
	}

	std::cout << anim->GetPosition().x << " , " << anim->GetPosition().y << std::endl;
	std::cout << shape2->GetPosition().x << " , " << shape2->GetPosition().y << std::endl;
	//std::cout << anim->GetScale().x << " , " << anim->GetScale().y << std::endl;
}