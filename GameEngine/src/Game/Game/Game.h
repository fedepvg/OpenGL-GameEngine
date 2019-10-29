#ifndef GAME_H
#define GAME_H

#include "Engine/BaseGame.h"
#include "Engine/Shape.h"

class Game : public BaseGame
{
//private:
//	BaseGame* bg;
public:
	Game(int width, int height);
	~Game();
	void Init();
	void Update();
private:
	Shape shape;
};

#endif