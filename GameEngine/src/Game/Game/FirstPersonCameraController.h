#ifndef FIRSTPERSONCAMERACONTROLLER_H
#define FIRSTPERSONCAMERACONTROLLER_H

#include "Engine/Cursor.h"
#include "Engine/Camera.h"

class FirstPersonCameraController
{
public:
	FirstPersonCameraController(Camera* newCamera, Cursor* newCursor);
	~FirstPersonCameraController();
	void Update();
	void SetSensitivity(float newSensitivity);
	void TranslateX(float distance);
	void TranslateY(float distance);
	float pitchLimit;

private:
	Camera* camera;
	Cursor* cursor;
	float sensitivity = 1.f;
	float offsetX;
	float offsetY;
	float yaw;
	float pitch;
	double prevCursorX;
	double prevCursorY;
};

#endif // !FIRSTPERSONCAMERACONTROLLER_H