#ifndef	ANIMATION_H
#define ANIMATION_H

#define EXPORTDLL _declspec(dllexport)

#include "glm/glm.hpp"

class Animation
{
public:
	Animation(float spritesheetWidth, float frameWidth, int rows, int currentRow, int framesCount);
	glm::vec2 GetCurrentFrameCoords(int index);
	void UpdateAnimation();
	void SelectFrame(int frame);
private:
	glm::vec2 frameCoords[4];
	float spritesheetWidth;
	float frameWidth;
	int maxRows;
	int actualRow;
	int framesCount;
};

#endif