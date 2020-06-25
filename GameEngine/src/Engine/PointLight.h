#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#define EXPORTDLL _declspec(dllexport)

#include  <glm/glm.hpp>

class EXPORTDLL PointLight
{
public:
	PointLight();
	PointLight(glm::vec3 positionValue,
		glm::vec3 ambientValue, glm::vec3 diffuseValue, glm::vec3 specularValue,
		float constantValue, float linearValue, float quadraticValue);
	~PointLight();

	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float constant;
	float linear;
	float quadratic;
};

#endif