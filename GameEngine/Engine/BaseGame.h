#ifndef BASEGAME_H
#define BASEGAME_H
#define EXPORTDLL _declspec(dllexport)


class BaseGame
{
public:
	EXPORTDLL BaseGame();
	EXPORTDLL ~BaseGame();
	EXPORTDLL void test();
};

#endif