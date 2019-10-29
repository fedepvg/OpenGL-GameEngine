#ifndef BASEGAME_H
#define BASEGAME_H
#define EXPORTDLL _declspec(dllexport)

#include "Window.h"
#include "Renderer.h"
#include "Input.h"

class EXPORTDLL BaseGame
{
public:
	BaseGame(int screenWidth, int screenHeight);
	~BaseGame();
	int GameLoop();
	virtual void Update() = 0;
private:
	Window* window;
	Renderer* renderer;
protected:
	Input* input;
};

#endif