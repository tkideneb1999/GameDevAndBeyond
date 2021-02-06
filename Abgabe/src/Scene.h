#pragma once

#include <unordered_map>
#include <string>

#include "Entity.h"
#include "Rendering/RenderSystem.h"

class SceneGUI;
struct GLFWwindow;

class Scene
{
private:
	std::vector<Entity> entityList;
	entt::registry registry;
	int activeEntityIndex = -1;

	RenderSystem renderSystem;
public:
	Scene();
	void AddEntity();
	void RemoveEntity(int index);
	void SerializeScene(const char* filePath);
	void DeserializeScene(const char* filePath);

	void Update(double deltaTime);

	void OnWindowSizeChanged(GLFWwindow* window, int width, int height);

	friend class SceneGUI;
};