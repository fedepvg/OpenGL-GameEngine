#ifndef SHADER_H
#define SHADER_H

#define EXPORTDLL _declspec(dllexport)

#include <glm/glm.hpp>
#include <string>

class EXPORTDLL Shader
{
	unsigned int shaderIndex;
	
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void Use();
	void SetMat4(const std::string& name, const glm::mat4& value) const;
	void SetInt(const std::string& name, int value) const;
	
};

#endif