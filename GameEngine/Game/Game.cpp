#include "Game.h"
#include "BaseGame.h"

Game::Game()
{
	init();
}

Game::~Game()
{

}

void Game::init()
{
	BaseGame bg;
	bg.createWindow();
}