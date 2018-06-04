#include "Shader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Renderer.h"


ShaderSrc Shader::Parse(const std::string& filepath) {
	std::ifstream ifs(filepath);
	if (!ifs.is_open()) {
		std::cout << "error reading shaders from file!!!\n";
	}
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(ifs, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << "\n";
		}
	}
	return { ss[0].str(), ss[1].str() };
}

uint Shader::CreateShader(uint type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char *src = source.c_str();
	GlCall(glShaderSource(id, 1, &src, nullptr));
	GlCall(glCompileShader(id));

	// TODO: Error handling
	int result;
	GlCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		int length;
		GlCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(sizeof(char) * length); // alloca() for stack allocation dynamically
		GlCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "failed to compile "
			<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader: " << message << "\n";
		GlCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

uint Shader::CompileShader(const std::string &vertexShader, const std::string &fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CreateShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CreateShader(GL_FRAGMENT_SHADER, fragmentShader);

	GlCall(glAttachShader(program, vs));
	GlCall(glAttachShader(program, fs));
	GlCall(glLinkProgram(program));
	GlCall(glValidateProgram(program));

	GlCall(glDeleteShader(vs));
	GlCall(glDeleteShader(fs));

	return program;
}

Shader::Shader(const std::string& filepath)
{
	src = Parse("../res/shaders/basic.shader");
	renderer_id = CompileShader(src.vertex, src.fragment);
	GlCall(glUseProgram(renderer_id));
}

Shader::~Shader()
{
	GlCall(glDeleteProgram(renderer_id));
}

void Shader::Bind() const
{
	GlCall(glUseProgram(renderer_id));
}

void Shader::Unbind() const
{
	GlCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GlCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GlCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GlCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3)); //rgba	
}

int Shader::GetUniformLocation(const std::string& name)
{
	int location;
	if (locationCache.find(name) == locationCache.end()) {
		GlCall(location = glGetUniformLocation(renderer_id, name.c_str()));
	}
	else
		return locationCache[name];
	

	if (location == -1)
		std::cout << "Warning: shader has no uniform " << name << "!\n";
	
	locationCache[name] = location;
	return location;
}

