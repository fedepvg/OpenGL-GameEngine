#ifndef GAME_H
#define GAME_H

#include "Engine/BaseGame.h"
#include "Engine/Shape.h"
#include "Engine/Sprite.h"
#include "Engine/Model.h"
#include "FirstPersonCameraController.h"

class DirectionalLight;

class Game : public BaseGame
{
public:
	Game(int width, int height);
	~Game();
	void Init();
	void Update(const float deltaTime);
private:
	FirstPersonCameraController* fpsCamera;
	Shader* ourShader;
	Shape* shape;
	Shape* shape2;
	Sprite* anim;
	Model* testModel;
	DirectionalLight* dirLight;
	glm::vec2 safePosition;
	bool safePositionExists;
};

#endif