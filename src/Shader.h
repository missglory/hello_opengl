#pragma once 
#include <string>
#include <unordered_map>
#include "defines.h"
struct ShaderSrc {
	std::string vertex, fragment;
};

class Shader {
private:
	uint renderer_id;
	std::string filepath;
	ShaderSrc src;
	std::unordered_map<std::string, int> locationCache;
public:
	Shader(const std::string & filepath);
	~Shader();
	void Bind() const;
	void Unbind() const;
	void Shader::SetUniform1i(const std::string& name, int value);
	void Shader::SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	int GetUniformLocation(const std::string& name);

private:
	ShaderSrc Parse(const std::string& filepath);
	uint CreateShader(uint type, const std::string& source);
	uint CompileShader(const std::string& vertexShader, const std::string& fragmentShader); // type int or uint ???
	//uint GetUniformLocation(const std::string& name);
};