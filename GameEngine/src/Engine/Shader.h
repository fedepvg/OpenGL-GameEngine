#ifndef SHADER_H
#define SHADER_H

#define EXPORTDLL _declspec(dllexport)

#include <glm/glm.hpp>
#include <string>

class DirectionalLight;

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
	void SetMat4(const std::string& name, const glm::mat4& value) const;
	void SetVec3(const std::string& name, const glm::vec3& value) const;
	void SetInt(const std::string& name, int value) const;
	void PassDirectionalLightValues(DirectionalLight* dirLight);
};

#endif