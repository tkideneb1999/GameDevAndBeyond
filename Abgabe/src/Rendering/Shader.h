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
	Shader(const char* filePath);
	Shader();
	~Shader();
	Shader(const Shader& shader);

	void EnableShader();
	void DisableShader();

private:
	std::string m_Name;

	const char* m_ShaderLocation;

	GLuint m_ShaderProgram;
	std::unordered_map<const char*, GLint> m_UniformMap;

	void LoadSource(const char* filePath, std::string& outVertSource, std::string& outFragSource);

	GLchar* CopyToGLchar(std::string& source);

	void CheckShaderCompilationResult(GLuint ShaderObj);

	void CheckShaderLinkingResult(GLuint ShaderProgram);

	GLuint CreateShader(const GLchar* source, GLenum shaderType);

	void CreateShaderProgram(const char* filePath);

	GLuint CacheUniformLocation(const char* name);
	bool GetUniformLocation(const char* name, GLint* pLocation);

public:
	const char* GetShaderLocation() { return m_ShaderLocation; }

	void SetUniform1f(const char* name, float value);
	void SetUniform2f(const char* name, glm::vec2 value);
	void SetUniform3f(const char* name, glm::vec3 value);
	void SetUniform4f(const char* name, glm::vec4 value);
	void SetMatrix4x4(const char* name, glm::mat4x4);

	void GetUniform4f(const char* name, glm::vec4& value);
};