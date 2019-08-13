#ifndef BASEGAME_H
#define BASEGAME_H
#define EXPORTDLL _declspec(dllexport)


class EXPORTDLL BaseGame
{
public:
	BaseGame();
	~BaseGame();
	int createWindow();
};

#endif