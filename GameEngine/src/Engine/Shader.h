#ifndef SHADER_H
#define SHADER_H

#define EXPORTDLL _declspec(dllexport)

#include <glm/glm.hpp>
#include <string>
#include <list>

class DirectionalLight;
class PointLight;
class SpotLight;

struct DirLight {
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class EXPORTDLL Shader
{
	unsigned int shaderIndex;
	
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void Use();
	void SetMat4(const std::string& name, const glm::mat4& value);
	void SetVec3(const std::string& name, const glm::vec3& value);
	void SetInt(const std::string& name, int value);
	void SetFloat(const std::string& name, float value);
	void PassDirectionalLightValues(DirectionalLight* dirLight);
	void PassPointLightListValues(std::list<PointLight*> pointLightList);
	void PassSpotLightListValues(std::list<SpotLight*> spotLightList);
};

#endif