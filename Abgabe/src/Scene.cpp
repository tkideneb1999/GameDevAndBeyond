#include "Scene.h"

#include "Serialization/SceneArchive.h"
#include "Entity.h"

Scene::Scene()
{

}

void Scene::AddEntity()
{
	m_entityList.emplace_back(Entity(*this));
}

void Scene::RemoveEntity(int index)
{
	entt::entity entityHandle = m_entityList[index].entityHandle;
	m_entityList.erase(m_entityList.begin() + index);
	m_registry.destroy(entityHandle);
}

void Scene::SerializeScene(const char* filePath)
{
	SceneOutputArchive outputArchive(filePath);
	outputArchive.Serialize(m_entityList, "EntityList");
}

void Scene::DeserializeScene(const char* filePath)
{
	m_activeEntityIndex = -1;
	m_entityList.clear();
	SceneInputArchive inputArchive(filePath);
	inputArchive.Serialize<Entity, Scene&>(m_entityList, "EntityList", *this);
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