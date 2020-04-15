#ifndef CAMERA_H
#define CAMERA_H
#define EXPORTDLL _declspec(dllexport)

#include "glm/glm.hpp"

class EXPORTDLL Camera
{
public:
	Camera(glm::vec3 position);
	~Camera();
	void Rotate(float angle, glm::vec3 axis);
	void Translate(float value, glm::vec3 axis);
	glm::mat4 GetViewMatrix();
private:
	glm::mat4 viewMatrix;
	//glm::mat4 projMatrix;
	//glm::vec3 cameraTarget;

};
#endif