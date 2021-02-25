#pragma once

#include <vector>

#include "nlohmannJSON/json.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/quaternion.hpp"

using JsonType = nlohmann::ordered_json;

class SceneOutputArchive
{
private:
	JsonType m_rootJson;
	JsonType* m_pCurrentJson;
	std::string m_filePath;

public:
	SceneOutputArchive(const std::string& filePath);
	~SceneOutputArchive();

	void Serialize(bool& value, const std::string& label);
	void Serialize(float& value, const std::string& label);
	void Serialize(int& value, const std::string& label);
	void Serialize(unsigned long& value, const std::string& label);
	void Serialize(size_t& value, const std::string& label);
	void Serialize(std::string& value, const std::string& label);
	void Serialize(const char* value, const std::string& label) = delete;
	void Serialize(glm::vec2& value, const std::string& label);
	void Serialize(glm::vec3& value, const std::string& label);
	void Serialize(glm::vec4& value, const std::string& label);
	void Serialize(glm::quat& value, const std::string& label);

	template<typename T>
	void Serialize(T& serializable, const std::string& label)
	{
		JsonType* oldJson = m_pCurrentJson;
		JsonType inlinedJson;
		m_pCurrentJson = &inlinedJson;

		serializable.Serialize(*this);

		(*oldJson)[label] = *m_pCurrentJson;
		m_pCurrentJson = oldJson;
	}

	template<typename T>
	void Serialize(std::vector<T>& vector, const std::string& label)
	{
		JsonType* oldJson = m_pCurrentJson;
		JsonType inlinedJson;
		m_pCurrentJson = &inlinedJson;
		
		size_t size = vector.size();
		Serialize(size, "size");

		for (size_t i = 0; i < size; i++)
		{
			JsonType* vectorJson = m_pCurrentJson;
			JsonType elementJson;
			m_pCurrentJson = &elementJson;

			vector[i].Serialize(*this);

			(*vectorJson)[std::to_string(i)] = *m_pCurrentJson;
			m_pCurrentJson = vectorJson;
		}

		(*oldJson)[label] = *m_pCurrentJson;
		m_pCurrentJson = oldJson;
	}
};

class SceneInputArchive
{
private:
	JsonType m_rootJson;
	JsonType* m_pCurrentJson;

public:
	SceneInputArchive(const std::string& filePath);

	void Serialize(bool& value, const std::string& label);
	void Serialize(float& value, const std::string& label);
	void Serialize(int& value, const std::string& label);
	void Serialize(unsigned long& value, const std::string& label);
	void Serialize(size_t& value, const std::string& label);
	void Serialize(std::string& value, const std::string& label);
	void Serialize(const char* value, const std::string& label) = delete;
	void Serialize(glm::vec2& value, const std::string& label);
	void Serialize(glm::vec3& value, const std::string& label);
	void Serialize(glm::vec4& value, const std::string& label);
	void Serialize(glm::quat& value, const std::string& label);

	template<typename T>
	void Serialize(T& serializable, const std::string& label)
	{
		JsonType* oldJson = m_pCurrentJson;
		JsonType& inlinedJson = (*m_pCurrentJson)[label];
		m_pCurrentJson = &inlinedJson;

		serializable.Serialize(*this);

		m_pCurrentJson = oldJson;
	}

	template<typename T, typename... Args>
	void Serialize(std::vector<T>& vector, const std::string& label, Args... args)
	{
		JsonType* oldJson = m_pCurrentJson;
		JsonType& inlinedJson = (*m_pCurrentJson)[label];
		m_pCurrentJson = &inlinedJson;
		size_t size;
		Serialize(size, "size");
		vector.reserve(size);

		for (size_t i = 0; i < size; i++)
		{
			vector.emplace_back(args...);
			JsonType* vectorJson = m_pCurrentJson;
			JsonType& elementJson = (*m_pCurrentJson)[std::to_string(i)];
			m_pCurrentJson = &elementJson;
			vector.back().Serialize(*this);

			m_pCurrentJson = vectorJson;
		}


		m_pCurrentJson = oldJson;
	}
};