#pragma once

#include <unordered_map>
#include <string>

#include "entt/entt.hpp"

struct Entity
{
	entt::entity entity;
	std::string name;

	Entity() = delete;
	Entity(entt::entity entityID);
	Entity(entt::entity entityID, const char* name);
};

class Scene
{
private:
	std::vector<Entity> entityList;
	entt::registry registry;
public:
	Scene();
	void AddEntity();
	void RemoveEntity();
	void SaveScene(const char* filePath);
	void LoadScene(const char* filePath);

	void SetGUIWindowData();
};