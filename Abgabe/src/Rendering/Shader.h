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

	std::unordered_map<std::string, GLenum>& GetUniformTypeMap(){ return m_UniformTypeMap; }
	std::string GetName() { return m_Name; }

private:
	std::string m_Name;

	const char* m_ShaderLocation;

	GLuint m_ShaderProgramHandle;

	std::unordered_map<std::string, GLint> m_UniformMap;
	std::unordered_map<std::string, GLenum> m_UniformTypeMap;

	void CacheAllUniforms();

	GLchar* CopyToGLchar(std::string& source);

	//Check Compilation
	void CheckShaderCompilationResult(GLuint ShaderObj);
	void CheckShaderLinkingResult(GLuint ShaderProgram);

	//Create Shaders and Program
	GLuint CreateShader(const GLchar* source, GLenum shaderType);
	void CreateShaderProgram(const char* filePath);
	void LoadSource(const char* filePath, std::string& outVertSource, std::string& outFragSource);

	GLuint CacheUniformLocation(const char* name);
	bool GetUniformLocation(const char* name, GLint* pLocation);

public:
	const char* GetShaderLocation() { return m_ShaderLocation; }

	void EnableShader();
	void DisableShader();

	//Set Uniforms with string
	void SetUniform(const char* name, int value);
	void SetUniform(const char* name, float value);
	void SetUniform(const char* name, glm::vec2 value);
	void SetUniform(const char* name, glm::vec3 value);
	void SetUniform(const char* name, glm::vec4 value);
	void SetUniform(const char* name, glm::mat4x4 value);

	//Set Uniforms with IDs
	void SetUniform(GLint id, int value);
	void SetUniform(GLint id, float value);
	void SetUniform(GLint id, glm::vec2 value);
	void SetUniform(GLint id, glm::vec3 value);
	void SetUniform(GLint id, glm::vec4 value);
	void SetUniform(GLint id, glm::mat4x4 value);

	//Get Uniform
	void GetUniform4f(const char* name, glm::vec4& value);
};