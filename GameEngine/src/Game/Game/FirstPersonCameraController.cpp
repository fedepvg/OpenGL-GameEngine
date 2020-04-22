#include "FirstPersonCameraController.h"
#include "Engine/Input.h"

FirstPersonCameraController::FirstPersonCameraController(Camera* newCamera, Cursor* newCursor)
{
	cursor = newCursor;
	camera = newCamera;
	yaw = 0.f;
	pitch = 0.f;
	prevCursorX = cursor->GetCursorX();
	prevCursorY = cursor->GetCursorY();
}

FirstPersonCameraController::~FirstPersonCameraController() 
{

}

void FirstPersonCameraController::Update() 
{
	offsetX = cursor->GetCursorX() - prevCursorX;
	offsetY = prevCursorY - cursor->GetCursorY(); // reversed since y-coordinates range from bottom to top
	prevCursorX = cursor->GetCursorX();
	prevCursorY = cursor->GetCursorY();

	offsetX *= sensitivity;
	offsetY *= sensitivity;

	camera->RotatePitch(offsetY * sensitivity);
	camera->RotateYaw(offsetX * sensitivity);
}

void FirstPersonCameraController::SetSensitivity(float newSensitivity) 
{
	sensitivity = newSensitivity;
}

void FirstPersonCameraController::TranslateX(float distance)
{
	glm::vec3 moveVector = camera->GetRightVector();
	moveVector = glm::normalize(moveVector) * distance;
	camera->Translate(moveVector);
}

void FirstPersonCameraController::TranslateY(float distance) 
{
	glm::vec3 moveVector = camera->GetDirection();
	moveVector = glm::normalize(moveVector) * distance;
	camera->Translate(moveVector);
}