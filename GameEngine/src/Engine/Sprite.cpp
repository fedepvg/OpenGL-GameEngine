#include "Sprite.h"

#include "Animation.h"

Sprite::Sprite(glm::vec3 pos, glm::vec3 scale, Texture* tex) : Shape(pos, scale, tex)
{

}

void Sprite::CreateAnimation(float spritesheetWidth, float frameWidth, int maxRows, int row, int framesCount)
{
	animation = new Animation(spritesheetWidth, frameWidth, maxRows, row, framesCount);
}

void Sprite::SetCurrentAnimation(int row)
{

}

void Sprite::UpdateAnimation()
{

}

void Sprite::SelectFrame(int frame)
{

}