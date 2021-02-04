#include "Scene.h"
#include "ImGui/imgui.h"

Entity::Entity(entt::entity entityID)
	:entity(entityID), name("Entity")
{

}

Entity::Entity(entt::entity entityID, const char* objectName)
	:entity(entityID), name(objectName)
{

}

Scene::Scene()
{

}

void Scene::AddEntity()
{
	entt::entity entity = registry.create();
	entityList.emplace_back(Entity(entity));
}

void Scene::RemoveEntity()
{

}

void Scene::SaveScene(const char* filePath)
{

}

void Scene::LoadScene(const char* filePath)
{

}

void Scene::SetGUIWindowData()
{
	ImGui::Begin("Scene");
	if (ImGui::Button("Add Entity"))
	{
		AddEntity();
	}
	ImGui::BeginChild("Entities");
	for (auto entity : entityList)
	{
		if (ImGui::Button(entity.name.c_str()));
	}
	ImGui::EndChild();
	ImGui::End();
}