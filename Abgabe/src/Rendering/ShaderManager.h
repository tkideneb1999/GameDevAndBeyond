#pragma once

#include <unordered_map>

#include "Shader.h"

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	static ShaderManager& Get() { return s_instance; }
	ShaderManager(const ShaderManager&) = delete;

	Shader* GetShader(std::string& name);
	void GetShaderNames(std::vector<std::string>& shaderNames);
	bool RegisterShader(const char* sourcePath);
private:
	static ShaderManager s_instance;
	std::unordered_map<std::string, Shader*> m_ShaderLookup;
};