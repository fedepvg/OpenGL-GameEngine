#ifndef GAME_H
#define GAME_H

#include "Engine/BaseGame.h"
#include "Engine/Shape.h"
#include "Engine/Sprite.h"
#include "FirstPersonCameraController.h"

class Game : public BaseGame
{
public:
	Game(int width, int height);
	~Game();
	void Init();
	void Update(const float deltaTime);
private:
	FirstPersonCameraController* fpsCamera;
	Shape* shape;
	Shape* shape2;
	Sprite* anim;
	glm::vec2 safePosition;
	bool safePositionExists;
};

#endif