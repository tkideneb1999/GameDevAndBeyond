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
	Shader(const Shader& shader);

	void EnableShader();
	void DisableShader();

private:
	const char* m_VertShaderLocation;
	const char* m_FragShaderLocation;

	GLuint m_ShaderProgram;
	std::unordered_map<const char*, GLint> m_UniformMap;

	const GLchar* LoadSource(const char* filePath);

	void CheckShaderCompilationResult(GLuint ShaderObj);

	void CheckShaderLinkingResult(GLuint ShaderProgram);

	GLuint CreateShader(const char* sourcePath, GLenum type);

	GLuint CacheUniformLocation(const char* name);
	bool GetUniformLocation(const char* name, GLint* pLocation);

public:
	const char* GetVertShaderLocation() { return m_VertShaderLocation; }
	const char* GetFragShaderLocation() { return m_FragShaderLocation; }
	void SetUniform1f(const char* name, float value);
	void SetUniform2f(const char* name, glm::vec2 value);
	void SetUniform3f(const char* name, glm::vec3 value);
	void SetUniform4f(const char* name, glm::vec4 value);
	void SetMatrix4x4(const char* name, glm::mat4x4);

	void GetUniform4f(const char* name, glm::vec4& value);
};