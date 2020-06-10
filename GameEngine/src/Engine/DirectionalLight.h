#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#define EXPORTDLL _declspec(dllexport)

#include  <glm/glm.hpp>

class EXPORTDLL DirectionalLight
{
public:
	DirectionalLight();
	DirectionalLight(glm::vec3 direction, glm::vec3 ambientValue, glm::vec3 diffuseValue, glm::vec3 specularValue);
	~DirectionalLight();

	glm::vec3 dir;
	glm::vec3 ambient = { 0.1f,0.1f,0.1f };
	glm::vec3 diffuse = { 0.7f,0.7f,0.7f };
	glm::vec3 specular;
};

#endif