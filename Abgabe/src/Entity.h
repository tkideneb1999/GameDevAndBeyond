#pragma once

#include <string>

#include "entt/entt.hpp"

#include "Scene.h"
#include "Serialization/SceneArchive.h"

class EntityGUI;

class Entity
{
private:
	Scene* m_pScene;
public:
	entt::entity entity;
	std::string name;

	Entity() = delete;

	Entity(entt::entity entityID, Scene& scene);
	Entity(entt::entity entityID, const char* objectName, Scene& scene);

	template<typename T>
	bool HasComponent()
	{
		return m_pScene->m_registry.has<T>(entity);
	}

	template<typename T>
	T& GetComponent()
	{
		return m_pScene->m_registry.get<T>(entity);
	}

	void Serialize(SceneOutputArchive& outputArchive);

	friend class EntityGUI;
};