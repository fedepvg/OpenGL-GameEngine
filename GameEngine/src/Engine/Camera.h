#ifndef CAMERA_H
#define CAMERA_H
#define EXPORTDLL _declspec(dllexport)

#include "glm/glm.hpp"

class EXPORTDLL Camera
{
public:
	Camera(glm::vec3 newPosition, glm::vec3 up, glm::vec3 newDirection, float newYaw, float newPitch);
	~Camera();
	void Update();
	void RotatePitch(float angle);
	void RotateYaw(float angle);
	void Translate(glm::vec3 translationVector);
	glm::vec3 GetRightVector();
	glm::vec3 GetDirection();
	glm::mat4 GetViewMatrix();
private:
	float yaw;
	float pitch;
	glm::mat4 viewMatrix;
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 upVector;
	glm::vec3 worldUp;
	glm::vec3 rightVector;
};
#endif