#ifndef GAME_H
#define GAME_H

#include "Engine/BaseGame.h"
#include "Engine/Model.h"
#include "FirstPersonCameraController.h"

class DirectionalLight;
class PointLight;

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
	Model* testModel;
	DirectionalLight* dirLight;
	std::list<PointLight*> pointLightList;
};

#endif