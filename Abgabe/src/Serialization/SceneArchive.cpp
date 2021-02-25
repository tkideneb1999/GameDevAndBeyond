#include "SceneArchive.h"

#include <fstream>

#include "CustomTypeSerializationJson.h"

#pragma region SceneOutputArchiveImpl

SceneOutputArchive::SceneOutputArchive(const std::string& filePath)
	:m_pCurrentJson(&m_rootJson), m_filePath(filePath)
{
	
}

SceneOutputArchive::~SceneOutputArchive()
{
	std::ofstream filestream(m_filePath);
	filestream << m_rootJson.dump(4);
}

void SceneOutputArchive::Serialize(bool& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void SceneOutputArchive::Serialize(float& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void SceneOutputArchive::Serialize(int& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void SceneOutputArchive::Serialize(unsigned long& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void SceneOutputArchive::Serialize(size_t& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void SceneOutputArchive::Serialize(std::string& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void SceneOutputArchive::Serialize(glm::vec2& value, const std::string& label)
{
	JsonType inlinedJson;

	inlinedJson["x"] = value.x;
	inlinedJson["y"] = value.y;

	(*m_pCurrentJson)[label] = inlinedJson;
}

void SceneOutputArchive::Serialize(glm::vec3& value, const std::string& label)
{
	JsonType inlinedJson;

	inlinedJson["x"] = value.x;
	inlinedJson["y"] = value.y;
	inlinedJson["z"] = value.z;

	(*m_pCurrentJson)[label] = inlinedJson;
}

void SceneOutputArchive::Serialize(glm::vec4& value, const std::string& label)
{
	JsonType inlinedJson;

	inlinedJson["x"] = value.x;
	inlinedJson["y"] = value.y;
	inlinedJson["z"] = value.z;
	inlinedJson["w"] = value.z;

	(*m_pCurrentJson)[label] = inlinedJson;
}

void SceneOutputArchive::Serialize(glm::quat& value, const std::string& label)
{
	JsonType inlinedJson;

	inlinedJson["qw"] = value.w;
	inlinedJson["qx"] = value.x;
	inlinedJson["qy"] = value.y;
	inlinedJson["qz"] = value.z;

	(*m_pCurrentJson)[label] = inlinedJson;
}

#pragma endregion



#pragma region SceneInputArchiveImpl

SceneInputArchive::SceneInputArchive(const std::string& filePath)
	:m_pCurrentJson(&m_rootJson)
{
	std::ifstream filestream(filePath);
	filestream >> m_rootJson;
}

void SceneInputArchive::Serialize(bool& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<bool>();
}

void SceneInputArchive::Serialize(float& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<float>();
}

void SceneInputArchive::Serialize(int& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<int>();
}

void SceneInputArchive::Serialize(unsigned long& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<unsigned long>();
}

void SceneInputArchive::Serialize(size_t& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<size_t>();
}

void SceneInputArchive::Serialize(std::string& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<std::string>();
}

void SceneInputArchive::Serialize(glm::vec2& value, const std::string& label)
{
	JsonType& inlinedJson = (*m_pCurrentJson)[label];
	value.x = inlinedJson["x"].get<float>();
	value.y = inlinedJson["y"].get<float>();
}

void SceneInputArchive::Serialize(glm::vec3& value, const std::string& label)
{
	JsonType& inlinedJson = (*m_pCurrentJson)[label];
	value.x = inlinedJson["x"].get<float>();
	value.y = inlinedJson["y"].get<float>();
	value.z = inlinedJson["z"].get<float>();
}

void SceneInputArchive::Serialize(glm::vec4& value, const std::string& label)
{
	JsonType& inlinedJson = (*m_pCurrentJson)[label];
	value.x = inlinedJson["x"].get<float>();
	value.y = inlinedJson["y"].get<float>();
	value.z = inlinedJson["z"].get<float>();
	value.w = inlinedJson["w"].get<float>();
}

void SceneInputArchive::Serialize(glm::quat& value, const std::string& label)
{
	JsonType& inlinedJson = (*m_pCurrentJson)[label];
	value.w = inlinedJson["qw"].get<float>();
	value.x = inlinedJson["qx"].get<float>();
	value.y = inlinedJson["qy"].get<float>();
	value.z = inlinedJson["qz"].get<float>();
}

#pragma endregion