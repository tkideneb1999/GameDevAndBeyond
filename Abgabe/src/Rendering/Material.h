#pragma once

#include <unordered_map>
#include <string>

#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

#include "Shader.h"

class Material
{
private:
	std::string m_Name;
	std::string m_Location;
	Shader* m_pShader;
	std::unordered_map<std::string, int> m_iUniforms;
	std::unordered_map<std::string, float> m_fUniforms;
	std::unordered_map<std::string, glm::vec2> m_v2Uniforms;
	std::unordered_map<std::string, glm::vec3> m_v3Uniforms;
	std::unordered_map<std::string, glm::vec4> m_v4Uniforms;
	std::unordered_map<std::string, glm::mat4> m_m4Uniforms;

public:
	Material();
	Material(const char* filePath);
	~Material();
	Material(const Material& mat);

	void SerializeMaterial(const char* filePath);

	void SetShader(std::string shaderName);
	Shader* GetShader() { return m_pShader; }

	void SetUniform(const char* name, float value);
	void SetUniform(const char* name, glm::vec2 value);
	void SetUniform(const char* name, glm::vec3 value);
	void SetUniform(const char* name, glm::vec4 value);
	void SetUniform(const char* name, glm::mat4x4 value);

	void TansferUniforms();

private:
	void GetUniformsFromShader();
};