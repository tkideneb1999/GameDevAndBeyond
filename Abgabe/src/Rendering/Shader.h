#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "GL/glew.h"

class Shader
{
public:
	Shader(const char* vertShaderPath, const char* fragShaderPath);
	~Shader();

	void EnableShader();
private:

	GLuint m_ShaderProgram;

	const GLchar* LoadSource(const char* filePath);

	void CheckShaderCompilationResult(GLuint ShaderObj);

	void CheckShaderLinkingResult(GLuint ShaderProgram);

	GLuint CreateShader(const char* sourcePath, GLenum type);
};