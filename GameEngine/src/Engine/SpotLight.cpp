#include "SpotLight.h"

SpotLight::SpotLight()
{
}

SpotLight::SpotLight(glm::vec3 positionValue, glm::vec3 directionValue, float cutOffValue, float outerCutOffValue,
	glm::vec3 ambientValue,	glm::vec3 diffuseValue, glm::vec3 specularValue,
	float constantValue, float linearValue, float quadraticValue)
{
	position = positionValue;
	direction = directionValue;
	cutOff = cutOffValue;
	outerCutOff = outerCutOffValue;
	
	ambient = ambientValue;
	diffuse = diffuseValue;
	specular = specularValue;

	constant = constantValue;
	linear = linearValue;
	quadratic = quadraticValue;
}

SpotLight::~SpotLight()
{
}
