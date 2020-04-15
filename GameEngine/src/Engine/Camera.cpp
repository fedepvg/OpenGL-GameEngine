#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(glm::vec3 position)
{
	viewMatrix = glm::lookAt(
		position, // position
		glm::vec3(0.0f, 0.0f, 0.0f), // look at
		glm::vec3(0.0f, 1.0f, 0.0f)  // up
	);
}


Camera::~Camera()
{
}
