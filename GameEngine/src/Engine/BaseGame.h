#ifndef BASEGAME_H
#define BASEGAME_H
#define EXPORTDLL _declspec(dllexport)

#include <list>

#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "ColisionManager.h"

class Entity;

class EXPORTDLL BaseGame
{
public:
	BaseGame(int screenWidth, int screenHeight);
	~BaseGame();
	int GameLoop();
	virtual void Update() = 0;
	std::list<Entity*> static entityList;
private:
	Window* window;
	Renderer* renderer;
protected:
	Input* input;
	ColisionManager* collisionManager;
};

#endif