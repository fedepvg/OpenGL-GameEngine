#ifndef	SPRITE_H
#define SPRITE_H

#define EXPORTDLL _declspec(dllexport)

#include "Shape.h"

#include "glm/glm.hpp"

class Animation;

class Sprite : public Shape
{
private:
	Animation* animation;
public:
	Sprite(glm::vec3 pos, glm::vec3 scale, Texture* tex);
	~Sprite();
	void SetAnimation(int framesCount, float frameWidth, float spritesheetWidth);
	void UpdateAnimation();
	void GoToNextFrame();
};

#endif