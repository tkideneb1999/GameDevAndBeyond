#pragma once

#include <string>
#include <fstream>
#include <unordered_map>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace MaterialSerialization
{
	class MaterialOutputArchive
	{
	public:
		MaterialOutputArchive(std::string& filePath, std::string& shaderName);
		~MaterialOutputArchive();

		void Serialize(int value, const std::string& label);
		void Serialize(float value, const std::string& label);

		void Serialize(glm::vec2 value, const std::string& label);
		void Serialize(glm::vec3 value, const std::string& label);
		void Serialize(glm::vec4 value, const std::string& label);

	private:
		std::ofstream m_fileStream;
	};

	void LoadMaterial(const char* filePath, std::string& shadername,
		std::unordered_map<std::string, int>& iUniforms, 
		std::unordered_map<std::string, float>& fUniforms, 
		std::unordered_map<std::string, glm::vec2>& v2Uniforms, 
		std::unordered_map<std::string, glm::vec3>& v3Uniforms, 
		std::unordered_map<std::string, glm::vec4>& v4Uniforms);
}