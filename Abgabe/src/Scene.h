#pragma once

#include <unordered_map>
#include <string>

#include "Entity.h"

class SceneGUI;

class Scene
{
private:
	std::vector<Entity> entityList;
	entt::registry registry;
	int activeEntityIndex = -1;
public:
	Scene();
	void AddEntity();
	void RemoveEntity(int index);
	void SerializeScene(const char* filePath);
	void DeserializeScene(const char* filePath);

	friend class SceneGUI;
};