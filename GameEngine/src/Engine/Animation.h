#ifndef	ANIMATION_H
#define ANIMATION_H

#define EXPORTDLL _declspec(dllexport)

#include "glm/glm.hpp"

class Animation
{
public:
	glm::vec2 GetCurrentFrameCoords(int index);
	void UpdateAnimation();
	void GoToNextFrame();
private:
	glm::vec2 frameCoords[4];
	int framesCount;
	float frameWidth;
	float spritesheetWidth;
};

#endif