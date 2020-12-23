#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "GL/glew.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

class Shader
{
public:
	Shader(const char* vertShaderPath, const char* fragShaderPath);
	Shader();
	~Shader();

	void EnableShader();
	void DisableShader();
private:

	GLuint m_ShaderProgram;
	std::unordered_map<const char*, GLuint> m_UniformMap;

	const GLchar* LoadSource(const char* filePath);

	void CheckShaderCompilationResult(GLuint ShaderObj);

	void CheckShaderLinkingResult(GLuint ShaderProgram);

	GLuint CreateShader(const char* sourcePath, GLenum type);

	GLuint CacheUniformLocation(const char* name);

public:
	void SetUniform1f(const char* name, float value);
	void SetUniform2f(const char* name, glm::vec2 value);
	void SetUniform3f(const char* name, glm::vec3 value);
	void SetUniform4f(const char* name, glm::vec4 value);
	void SetMatrix4x4(const char* name, glm::mat4x4);
};