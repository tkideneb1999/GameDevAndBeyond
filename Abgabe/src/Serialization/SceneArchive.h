#pragma once

#include "nlohmannJSON/json.hpp"

#include "../Entity.h"
#include "../Rendering/Transform.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/Camera.h"

class SceneInputArchive
{
	
};

class SceneOutputArchive
{
private:
	nlohmann::json m_rootJson;
	nlohmann::json* m_pCurrentJson;
	std::string m_filePath;
	entt::registry* m_pRegistry;

public:
	SceneOutputArchive(const std::string& filePath, entt::registry* pRegistry);
	~SceneOutputArchive();

	void Serialize(Entity& entity);
	void Serialize(Transform& transform);
	void Serialize(Mesh& mesh);
	void Serialize(Camera& camera);

	template<typename T>
	void Serialize(entt::entity entity)
	{
		if (m_pRegistry->any<T>(entity))
		{
			T& component = m_pRegistry->get<T>(entity);
			Serialize(component);
		}
	}
};