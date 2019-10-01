#include "Game.h"
#include "Engine/BaseGame.h"
#include "Engine/Shape.h"

Game::Game()
{
	Init();
}

Game::~Game()
{
	delete bg;
}

void Game::Init()
{
	bg = new BaseGame(800,600);
}