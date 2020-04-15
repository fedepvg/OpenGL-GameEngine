#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

Camera::Camera(vec3 position)
{
	viewMatrix = lookAt(
		position,
		vec3(0.0f, 0.0f, 0.0f), // look at
		vec3(0.0f, 1.0f, 0.0f)  // up
	);
}


Camera::~Camera()
{
}

void Camera::Rotate(float angle, vec3 axis) 
{
	viewMatrix = rotate(viewMatrix, radians(angle), axis);
}

void Camera::Translate(float value, vec3 axis) 
{
	viewMatrix = translate(viewMatrix, value * normalize(axis));
}

glm::mat4 Camera::GetViewMatrix() 
{
	return viewMatrix;
}