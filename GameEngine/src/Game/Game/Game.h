#ifndef GAME_H
#define GAME_H

#include "Engine/BaseGame.h"

class Game
{
private:
	BaseGame* bg;
public:
	Game();
	~Game();
	void Init();
};

#endif