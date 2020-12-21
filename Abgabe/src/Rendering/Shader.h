#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include <unordered_map>

#include "GL/glew.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

class Shader
{
public:
	Shader(const char* vertShaderPath, const char* fragShaderPath);

	void EnableShader();
private:

	GLuint m_ShaderProgram;
	std::unordered_map<const char*, GLuint> uniformMap;

	const GLchar* LoadSource(const char* filePath);

	void CheckShaderCompilationResult(GLuint ShaderObj);

	void CheckShaderLinkingResult(GLuint ShaderProgram);

	GLuint CreateShader(const char* sourcePath, GLenum type);

	GLuint CacheUniformLocation(const char* name);

public:
	void SetUniform1f(const char* name, float value);
	void SetUniform2f(const char* name, glm::vec2 value);
};