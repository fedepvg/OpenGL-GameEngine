#ifndef SHAPE_H
#define SHAPE_H
#define EXPORTDLL _declspec(dllexport)
#include "GLFW/glfw3.h"
#include <list>
class EXPORTDLL Shape
{
private:
	std::list<GLuint> vertexList;
	std::list<GLuint> elementList;
public:
	Shape();
	~Shape();

};
#endif // !SHAPE_H