#ifndef COLISIONMANAGER_H
#define COLISIONMANAGER_H

class Shape;

#define EXPORTDLL _declspec(dllexport)

class EXPORTDLL ColisionManager
{
public:
	ColisionManager() {};
	~ColisionManager() {};
	bool CheckCollision(Shape shape1, Shape shape2);
};

#endif
