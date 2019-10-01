#ifndef BASEGAME_H
#define BASEGAME_H
#define EXPORTDLL _declspec(dllexport)

class Window;
class Renderer;
class Input;

class EXPORTDLL BaseGame
{
public:
	BaseGame(int screenWidth, int screenHeight);
	~BaseGame();
	int GameLoop();
private:
	Window* window;
	Renderer* renderer;
	Input* input;
};

#endif