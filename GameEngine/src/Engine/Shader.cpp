#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"

#include "LoadShader.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include  "SpotLight.h"

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char * vertexShaderPath, const char * fragmentShaderPath)
{
	shaderIndex = LoadShaders(vertexShaderPath, fragmentShaderPath);
}

void Shader::Use()
{
	GLint currProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
	if(currProgram != shaderIndex)
		glUseProgram(shaderIndex);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value)
{
	Use();
	glUniformMatrix4fv(glGetUniformLocation(shaderIndex, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) 
{
	Use();
	glUniform3fv(glGetUniformLocation(shaderIndex, name.c_str()), 1, glm::value_ptr(value));
}


void Shader::SetInt(const std::string& name, int value)
{
	Use();
	glUniform1i(glGetUniformLocation(shaderIndex, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) 
{
	Use();
	glUniform1f(glGetUniformLocation(shaderIndex, name.c_str()), value);
}

void Shader::PassDirectionalLightValues(DirectionalLight* dirLight)
{
	Use();
	SetVec3("dirLight.direction", dirLight->dir);
	SetVec3("dirLight.ambient", dirLight->ambient);
	SetVec3("dirLight.diffuse", dirLight->diffuse);
	SetVec3("dirLight.specular", dirLight->specular);
}

void Shader::PassPointLightListValues(std::list<PointLight*> pointLightList)
{
	Use();
	int lightPosition = 0;
	for (std::list<PointLight*>::iterator it = pointLightList.begin(); it!= pointLightList.end(); it++)
	{
		SetVec3((std::string)"pointLights[" + std::to_string(lightPosition) + (std::string)"].position", (*it)->position);
		
		SetVec3((std::string)"pointLights[" + std::to_string(lightPosition) + (std::string)"].ambient", (*it)->ambient);
		SetVec3((std::string)"pointLights[" + std::to_string(lightPosition) + (std::string)"].diffuse", (*it)->diffuse);
		SetVec3((std::string)"pointLights[" + std::to_string(lightPosition) + (std::string)"].specular", (*it)->specular);
		
		SetFloat((std::string)"pointLights[" + std::to_string(lightPosition) + (std::string)"].constant", (*it)->constant);
		SetFloat((std::string)"pointLights[" + std::to_string(lightPosition) + (std::string)"].linear", (*it)->linear);
		SetFloat((std::string)"pointLights[" + std::to_string(lightPosition) + (std::string)"].quadratic", (*it)->quadratic);
		
		lightPosition++;
	}
}

void Shader::PassSpotLightListValues(std::list<SpotLight*> spotLightList)
{
	Use();
	int lightPosition = 0;
	for (std::list<SpotLight*>::iterator it = spotLightList.begin(); it != spotLightList.end(); it++)
	{
		SetVec3((std::string)"spotLights[" + std::to_string(lightPosition) + (std::string)"].position", (*it)->position);
		SetVec3((std::string)"spotLights[" + std::to_string(lightPosition) + (std::string)"].direction", (*it)->direction);
		SetFloat((std::string)"spotLights[" + std::to_string(lightPosition) + (std::string)"].cutOff", glm::cos(glm::radians((*it)->cutOff)));
		SetFloat((std::string)"spotLights[" + std::to_string(lightPosition) + (std::string)"].outerCutOff", glm::cos(glm::radians((*it)->outerCutOff)));
		
		SetVec3((std::string)"spotLights[" + std::to_string(lightPosition) + (std::string)"].ambient", (*it)->ambient);
		SetVec3((std::string)"spotLights[" + std::to_string(lightPosition) + (std::string)"].diffuse", (*it)->diffuse);
		SetVec3((std::string)"spotLights[" + std::to_string(lightPosition) + (std::string)"].specular", (*it)->specular);

		SetFloat((std::string)"spotLights[" + std::to_string(lightPosition) + (std::string)"].constant", (*it)->constant);
		SetFloat((std::string)"spotLights[" + std::to_string(lightPosition) + (std::string)"].linear", (*it)->linear);
		SetFloat((std::string)"spotLights[" + std::to_string(lightPosition) + (std::string)"].quadratic", (*it)->quadratic);
		
		lightPosition++;
	}
}
