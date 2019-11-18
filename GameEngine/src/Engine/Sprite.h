#ifndef	SPRITE_H
#define SPRITE_H

#define EXPORTDLL _declspec(dllexport)

#include "Shape.h"

#include "glm/glm.hpp"

class Animation;

class EXPORTDLL Sprite : public Shape
{
private:
	Animation* animation;
public:
	Sprite(glm::vec3 pos, glm::vec3 scale, Texture* tex) : Shape(pos, scale, tex) {};
	void CreateAnimation(float spritesheetWidth, float frameWidth, int maxRows, int row, int framesCount);
	void SetCurrentAnimation(int row);
	void UpdateCurrentAnimation(float timer);
	void SelectFrame(int frame);
};

#endif