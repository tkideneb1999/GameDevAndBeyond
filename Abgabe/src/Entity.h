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
	entt::entity entityHandle;
	std::string name;

	Entity() = delete;

	Entity(Scene& scene) noexcept;
	Entity(const char* objectName, Scene& scene) noexcept;
	Entity(const Entity& entity) = default;
	Entity(Entity&& entity) = default;

	~Entity() = default;

	Entity& operator= (const Entity& entity) = default;

	template<typename T>
	bool HasComponent()
	{
		return m_pScene->m_registry.has<T>(entityHandle);
	}

	template<typename T>
	T& GetComponent()
	{
		return m_pScene->m_registry.get<T>(entityHandle);
	}

	template<typename T>
	T& AddComponent()
	{
		if (HasComponent<T>())
		{
			std::cout << "Entity already has this Component, returning already existing one" << std::endl;
			return GetComponent<T>();
		}
		else
		{
			return m_pScene->m_registry.emplace<T>(entityHandle);
		}
	}

	void Serialize(SceneOutputArchive& outputArchive);
	void Serialize(SceneInputArchive& inputArchive);

	friend class EntityGUI;
};