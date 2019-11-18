#include "Animation.h"

Animation::Animation(float spritesheetWidth, float frameWidth, int rows, int currentRow, int framesCount)
{
	this->spritesheetWidth = spritesheetWidth;
	this->frameWidth = frameWidth;
	maxRows = rows;
	actualRow = currentRow;
	this->framesCount = framesCount;
}

void Animation::UpdateAnimation()
{

}

glm::vec2 Animation::GetCurrentFrameCoords(int index)
{
	return frameCoords[index];
}