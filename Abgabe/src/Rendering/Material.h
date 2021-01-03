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
	Shader* m_pShader;
	std::unordered_map<const char*, int> m_IParameters;
	std::unordered_map<const char*, float> m_FParameters;
	std::unordered_map<const char*, glm::vec2> m_V2Parameters;
	std::unordered_map<const char*, glm::vec3> m_V3Parameters;
	std::unordered_map<const char*, glm::vec4> m_V4Parameters;
	std::unordered_map<const char*, glm::mat4> m_M4Parameters;

public:
	Material();
	Material(const char* filePath);
	~Material();
	Material(const Material& mat);

	void SetShader(const char* shaderName);
	Shader* GetShader() { return m_pShader; }
};