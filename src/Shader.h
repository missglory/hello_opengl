#pragma once 
#include <string>
#include <unordered_map>
#include "defines.h"
#include "vendor/glm/glm.hpp"

struct ShaderSrc {
	std::string vertex, fragment;
};

class Shader {
private:
	uint renderer_id;
	std::string filepath;
	ShaderSrc src;
	std::unordered_map<std::string, int> locationCache; // for optimization
public:
	Shader(const std::string & filepath);
	~Shader();
	void Bind() const;
	void Unbind() const;
    void SetUniform1i(const std::string& name, int value);
    void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	int GetUniformLocation(const std::string& name);
	void SetUniformMat4f(const std::string& name, glm::mat4& matrix);
private:
	ShaderSrc Parse(const std::string& filepath);
	uint CreateShader(uint type, const std::string& source);
	uint CompileShader(const std::string& vertexShader, const std::string& fragmentShader);
};
