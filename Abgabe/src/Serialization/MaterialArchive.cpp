#include "MaterialArchive.h"

#include <sstream>

// ---------------------------------
// ---- Material Output Archive ----
// ---------------------------------
MaterialSerialization::MaterialOutputArchive::MaterialOutputArchive(std::string& filePath, std::string& shaderName)
	:m_fileStream(filePath)
{
	m_fileStream << "#Material\n";
	m_fileStream <<"Shader " << shaderName << "\n";
}

MaterialSerialization::MaterialOutputArchive::~MaterialOutputArchive()
{
	m_fileStream.close();
}

void MaterialSerialization::MaterialOutputArchive::Serialize(int value, const std::string& label)
{
	m_fileStream << "int " << label << " ";
	m_fileStream << value << "\n";
}

void MaterialSerialization::MaterialOutputArchive::Serialize(float value, const std::string& label)
{
	m_fileStream << "float " << label << " ";
	m_fileStream << value << "\n";
}

void MaterialSerialization::MaterialOutputArchive::Serialize(glm::vec2 value, const std::string& label)
{
	m_fileStream << "vec2 " << label << " ";
	m_fileStream << value.x << " " << value.y << "\n";
}

void MaterialSerialization::MaterialOutputArchive::Serialize(glm::vec3 value, const std::string& label)
{
	m_fileStream << "vec3 " << label << " ";
	m_fileStream << value.x << " " << value.y << " " << value.z << "\n";
}
void MaterialSerialization::MaterialOutputArchive::Serialize(glm::vec4 value, const std::string& label)
{
	m_fileStream << "vec4 " << label << " ";
	m_fileStream << value.x << " " << value.y << " " << value.z << " " << value.w << "\n";
}

// --------------------------------
// ---- Material Input Archive ----
// --------------------------------

void MaterialSerialization::LoadMaterial(const char* filePath, std::string& shadername,
	std::unordered_map<std::string, int>& iUniforms,
	std::unordered_map<std::string, float>& fUniforms,
	std::unordered_map<std::string, glm::vec2>& v2Uniforms,
	std::unordered_map<std::string, glm::vec3>& v3Uniforms,
	std::unordered_map<std::string, glm::vec4>& v4Uniforms)
{
	std::ifstream filestream(filePath);

	std::string currentLine;

	while (std::getline(filestream, currentLine, '\n'))
	{
		if (currentLine[0] == '#') continue;

		std::istringstream linestream(currentLine);
		std::string lineInfo;
		
		linestream >> lineInfo;
		if (lineInfo == "int")
		{
			linestream >> lineInfo;
			int value;
			linestream >> value;
			iUniforms.insert(std::make_pair(lineInfo, value));
		}
		else if (lineInfo == "float")
		{
			linestream >> lineInfo;
			float value;
			linestream >> value;
			fUniforms.insert(std::make_pair(lineInfo, value));
		}
		else if (lineInfo == "vec2")
		{
			linestream >> lineInfo;
			glm::vec2 value;
			linestream >> value.x;
			linestream >> value.y;
			v2Uniforms.insert(std::make_pair(lineInfo, value));
		}
		else if (lineInfo == "vec3")
		{
			linestream >> lineInfo;
			glm::vec3 value;
			linestream >> value.x;
			linestream >> value.y;
			linestream >> value.z;
			v3Uniforms.insert(std::make_pair(lineInfo, value));
		}
		else if (lineInfo == "vec4")
		{
			linestream >> lineInfo;
			glm::vec4 value;
			linestream >> value.x;
			linestream >> value.y;
			linestream >> value.z;
			linestream >> value.w;
			v4Uniforms.insert(std::make_pair(lineInfo, value));
		}
	}

	filestream.close();
}