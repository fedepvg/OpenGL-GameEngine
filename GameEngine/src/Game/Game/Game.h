#ifndef GAME_H
#define GAME_H

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