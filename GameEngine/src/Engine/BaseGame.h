#ifndef BASEGAME_H
#define BASEGAME_H
#define EXPORTDLL _declspec(dllexport)

#include "Window.h"
#include "Renderer.h"

class EXPORTDLL BaseGame
{
public:
	BaseGame();
	~BaseGame();
	int GameLoop();
private:
	Window window;
	Renderer renderer;
};

#endif