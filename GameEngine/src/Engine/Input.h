#ifndef INPUT_H
#define INPUT_H

#include "GLFW/glfw3.h"

class Input
{
public:
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);
};

#endif