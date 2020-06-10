#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
}

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambientValue, glm::vec3 diffuseValue,
	glm::vec3 specularValue)
{
	dir = direction;
	ambient = ambientValue;
	diffuse = diffuseValue;
	specular = specularValue;
}


DirectionalLight::~DirectionalLight()
{
}
