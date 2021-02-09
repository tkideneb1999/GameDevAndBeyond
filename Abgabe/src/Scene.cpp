#include "Scene.h"
#include "ImGui/imgui.h"
#include "Serialization/SceneArchive.h"

Scene::Scene()
{

}

void Scene::AddEntity()
{
	entt::entity entity = m_registry.create();
	m_entityList.emplace_back(Entity(entity));
}

void Scene::RemoveEntity(int index)
{
	entt::entity entity = m_entityList[index].entity;
	m_registry.remove_all(entity);
	m_registry.destroy(entity);
	m_entityList.erase(m_entityList.begin() + index);
}

void Scene::SerializeScene(const char* filePath)
{
	SceneOutputArchive archive(filePath, &m_registry);
	for (auto entity : m_entityList)
	{
		archive.Serialize(entity);
	}
}

void Scene::DeserializeScene(const char* filePath)
{

}

void Scene::Update(double deltaTime)
{
	renderSystem.Render(m_registry);
}

void Scene::OnWindowSizeChanged(GLFWwindow* window, int width, int height)
{
	auto cameraView = m_registry.view<Camera>();
	for (auto cameraEntity : cameraView)
	{
		Camera& camera = cameraView.get<Camera>(cameraEntity);
		camera.aspectRatio = (float)width / (float)height;
	}
}