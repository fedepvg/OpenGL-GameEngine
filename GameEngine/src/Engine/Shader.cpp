#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"

#include "LoadShader.h"
#include "DirectionalLight.h"
#include "PointLight.h"

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char * vertexShaderPath, const char * fragmentShaderPath)
{
	shaderIndex = LoadShaders(vertexShaderPath, fragmentShaderPath);
}

void Shader::Use()
{
	glUseProgram(shaderIndex);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderIndex, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(shaderIndex, name.c_str()), 1, glm::value_ptr(value));
}


void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(shaderIndex, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(shaderIndex, name.c_str()), value);
}

void Shader::PassDirectionalLightValues(DirectionalLight* dirLight)
{
	SetVec3("dirLight.direction", dirLight->dir);
	SetVec3("dirLight.ambient", dirLight->ambient);
	SetVec3("dirLight.diffuse", dirLight->diffuse);
	SetVec3("dirLight.specular", dirLight->specular);
}

void Shader::PassPointLightListValues(std::list<PointLight*> pointLightList)
{
	int lightPosition = 0;
	for (std::list<PointLight*>::iterator it = pointLightList.begin(); it!= pointLightList.end(); it++)
	{
		SetVec3((std::string)"pointLights[" + std::to_string(lightPosition) + (std::string)"].ambient", (*it)->ambient);
		SetVec3((std::string)"pointLights[" + std::to_string(lightPosition) + (std::string)"].diffuse", (*it)->diffuse);
		SetVec3((std::string)"pointLights[" + std::to_string(lightPosition) + (std::string)"].specular", (*it)->specular);
		SetVec3((std::string)"pointLights[" + std::to_string(lightPosition) + (std::string)"].position", (*it)->position);
		SetFloat((std::string)"pointLights[" + std::to_string(lightPosition) + (std::string)"].constant", (*it)->constant);
		SetFloat((std::string)"pointLights[" + std::to_string(lightPosition) + (std::string)"].linear", (*it)->linear);
		SetFloat((std::string)"pointLights[" + std::to_string(lightPosition) + (std::string)"].quadratic", (*it)->quadratic);
		lightPosition++;
	}
}
