#pragma once

#include <string>

#include "entt/entt.hpp"

class EntityGUI;

class Entity
{
public:
	entt::entity entity;
	std::string name;

	Entity() = delete;

	Entity(entt::entity entityID)
		:entity(entityID), name("Entity")
	{}

	Entity(entt::entity entityID, const char* objectName)
		:entity(entityID), name(objectName)
	{}

	friend class EntityGUI;
};