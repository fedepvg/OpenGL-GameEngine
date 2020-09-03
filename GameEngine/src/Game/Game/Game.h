#ifndef GAME_H
#define GAME_H

#include "Engine/BaseGame.h"
#include "Engine/Model.h"
#include "FirstPersonCameraController.h"

class DirectionalLight;
class PointLight;
class SpotLight;

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
	Model* testModel2;
	Model* testModel3;
	Model* testModel4;
	Model* bsp;
	DirectionalLight* dirLight;
	std::list<PointLight*> pointLightList;
	std::list<SpotLight*> spotLightList;
};

#endif