#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#define EXPORTDLL _declspec(dllexport)

#include  <glm/glm.hpp>

class EXPORTDLL SpotLight
{
public:
	glm::vec3 position;
	glm::vec3 direction;
	float cutOff;
	float outerCutOff;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;
	
	SpotLight();
	SpotLight(glm::vec3 positionValue, glm::vec3 directionValue, float cutOffValue, float outerCutOffValue,
		glm::vec3 ambientValue, glm::vec3 diffuseValue, glm::vec3 specularValue,
		float constantValue, float linearValue, float quadraticValue);
	~SpotLight();
};

#endif