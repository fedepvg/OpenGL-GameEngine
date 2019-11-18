#include "Animation.h"

Animation::Animation(float spritesheetWidth, float frameWidth, int rows, int currentRow, int framesCount)
{
	this->spritesheetWidth = spritesheetWidth;
	this->frameWidth = frameWidth;
	maxRows = rows;
	actualRow = currentRow;
	this->framesCount = framesCount;
	actualFrame = 0;
	frameSizeProportion.x = 1 / (spritesheetWidth / frameWidth);
	frameSizeProportion.y = 1 / (float)maxRows;
	frameTime = 0;
}

void Animation::UpdateAnimation(float timer)
{
	if (frameTime >= 0.25f)
	{
		frameTime = 0;
		actualFrame++;
		if (actualFrame >= framesCount)
			actualFrame = 0;
	}

	frameCoords[0] = { actualFrame * frameSizeProportion.x, (actualRow + 1) * frameSizeProportion.y}; //top left
	frameCoords[1] = { (actualFrame + 1) * frameSizeProportion.x, (actualRow + 1) * frameSizeProportion.y}; //top right
	frameCoords[2] = { actualFrame * frameSizeProportion.x, actualRow * frameSizeProportion.y}; //bottom left
	frameCoords[3] = { (actualFrame + 1) * frameSizeProportion.x, actualRow * frameSizeProportion.y}; //bottom right

	frameTime += timer;
}

glm::vec2 Animation::GetCurrentFrameCoords(int index)
{
	return frameCoords[index];
}

void Animation::SelectFrame(int frame)
{

}