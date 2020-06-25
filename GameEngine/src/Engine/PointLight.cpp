#include "PointLight.h"

PointLight::PointLight()
{
}

PointLight::PointLight(glm::vec3 positionValue, glm::vec3 ambientValue, glm::vec3 diffuseValue, glm::vec3 specularValue,
	float constantValue, float linearValue, float quadraticValue)
{
	position = positionValue;
	ambient = ambientValue;
	diffuse = diffuseValue;
	specular = specularValue;
	constant = constantValue;
	linear = linearValue;
	quadratic = quadraticValue;
}

PointLight::~PointLight()
{
}