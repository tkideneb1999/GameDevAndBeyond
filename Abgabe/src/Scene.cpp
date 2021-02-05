#include "Scene.h"
#include "ImGui/imgui.h"
#include "nlohmannJSON/json.hpp"

Scene::Scene()
{

}

void Scene::AddEntity()
{
	entt::entity entity = registry.create();
	entityList.emplace_back(Entity(entity));
}

void Scene::RemoveEntity(int index)
{
	entt::entity entity = entityList[index].entity;
	registry.remove_all(entity);
	registry.destroy(entity);
	entityList.erase(entityList.begin() + index);
}

void Scene::SerializeScene(const char* filePath)
{
	
}

void Scene::DeserializeScene(const char* filePath)
{

}