#include "SceneArchive.h"

#include <fstream>

#include "CustomTypeSerializationJson.h"

SceneOutputArchive::SceneOutputArchive(const std::string& filePath)
	:m_pCurrentJson(&m_rootJson), m_filePath(filePath)
{
	
}

SceneOutputArchive::~SceneOutputArchive()
{
	std::ofstream filestream(m_filePath);
	filestream << m_rootJson.dump(4);
}

void SceneOutputArchive::Serialize(bool value, std::string label)
{
	(*m_pCurrentJson)[label] = value;
}

void SceneOutputArchive::Serialize(float value, const std::string label)
{
	(*m_pCurrentJson)[label] = value;
}

void SceneOutputArchive::Serialize(int value, const std::string label)
{
	(*m_pCurrentJson)[label] = value;
}

void SceneOutputArchive::Serialize(unsigned long value, const std::string label)
{
	(*m_pCurrentJson)[label] = value;
}

void SceneOutputArchive::Serialize(size_t value, const std::string label)
{
	(*m_pCurrentJson)[label] = value;
}

void SceneOutputArchive::Serialize(std::string value, const std::string label)
{
	(*m_pCurrentJson)[label] = value;
}

void SceneOutputArchive::Serialize(const char* value, const std::string label)
{
	(*m_pCurrentJson)[label] = value;
}

void SceneOutputArchive::Serialize(glm::vec2 value, const std::string label)
{
	JsonType inlinedJson;

	inlinedJson["x"] = value.x;
	inlinedJson["y"] = value.y;

	(*m_pCurrentJson)[label] = inlinedJson;
}

void SceneOutputArchive::Serialize(glm::vec3 value, const std::string label)
{
	JsonType inlinedJson;

	inlinedJson["x"] = value.x;
	inlinedJson["y"] = value.y;
	inlinedJson["z"] = value.z;

	(*m_pCurrentJson)[label] = inlinedJson;
}

void SceneOutputArchive::Serialize(glm::vec4 value, const std::string label)
{
	JsonType inlinedJson;

	inlinedJson["x"] = value.x;
	inlinedJson["y"] = value.y;
	inlinedJson["z"] = value.z;
	inlinedJson["w"] = value.z;

	(*m_pCurrentJson)[label] = inlinedJson;
}

void SceneOutputArchive::Serialize(glm::quat value, const std::string label)
{
	JsonType inlinedJson;

	inlinedJson["qw"] = value.w;
	inlinedJson["qx"] = value.x;
	inlinedJson["qy"] = value.y;
	inlinedJson["qz"] = value.z;

	(*m_pCurrentJson)[label] = inlinedJson;
}