#ifndef	ANIMATION_H
#define ANIMATION_H

#define EXPORTDLL _declspec(dllexport)

#include "glm/glm.hpp"

class EXPORTDLL Animation
{
public:
	Animation(float spritesheetWidth, float frameWidth, int rows, int currentRow, int framesCount);
	glm::vec2 GetCurrentFrameCoords(int index);
	void UpdateAnimation(float timer);
	void SelectFrame(int frame);
	glm::vec2 frameCoords[4];
private:
	float spritesheetWidth;
	float frameWidth;
	int maxRows;
	int actualRow;
	int framesCount;
	int actualFrame;
	float frameTime;
	glm::vec2 frameSizeProportion;
};

#endif