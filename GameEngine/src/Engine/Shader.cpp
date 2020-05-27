#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"

#include "LoadShader.h"

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