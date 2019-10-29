#ifndef SHAPE_H
#define SHAPE_H
#define EXPORTDLL _declspec(dllexport)

#include "Entity.h"

class EXPORTDLL Shape : public Entity
{
public:
	Shape();
	~Shape();
private:
	void Render();
};
#endif // !SHAPE_H