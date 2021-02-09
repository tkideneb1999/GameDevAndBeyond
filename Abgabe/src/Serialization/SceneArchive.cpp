#include "SceneArchive.h"

#include <fstream>

#include "CustomTypeSerializationJson.h"

SceneOutputArchive::SceneOutputArchive(const std::string& filePath, entt::registry* pRegistry)
	:m_pCurrentJson(&m_rootJson), m_filePath(filePath), m_pRegistry(pRegistry)
{
	
}

SceneOutputArchive::~SceneOutputArchive()
{
	std::ofstream filestream(m_filePath);
	filestream << m_rootJson.dump(4);
}

void SceneOutputArchive::Serialize(Entity& entity)
{
	nlohmann::json* oldJson = m_pCurrentJson;
	nlohmann::json entityJson;
	m_pCurrentJson = &entityJson;

	entt::entity& entityID = entity.entity;

	Serialize<Transform>(entityID);
	Serialize<Mesh>(entityID);
	Serialize<Camera>(entityID);

	(*oldJson)[entity.name] = entityJson;
	m_pCurrentJson = oldJson;
}

void SceneOutputArchive::Serialize(Transform& transform)
{
	nlohmann::json* oldJson = m_pCurrentJson;
	nlohmann::json transformJson;
	m_pCurrentJson = &transformJson;

	transformJson["Position"] = transform.position;
	transformJson["Rotation"] = transform.rotation;
	transformJson["Scale"] = transform.scale;
	
	(*oldJson)["Transform"] = transformJson;
	m_pCurrentJson = oldJson;
}

void SceneOutputArchive::Serialize(Mesh& mesh)
{
	nlohmann::json* oldJson = m_pCurrentJson;
	nlohmann::json meshJson;
	m_pCurrentJson = &meshJson;

	meshJson["ModelPath"] = mesh.GetModelPath();
	meshJson["MaterialPath"] = mesh.material.GetMaterialLocation();

	(*oldJson)["Mesh"] = meshJson;
	m_pCurrentJson = oldJson;
}

void SceneOutputArchive::Serialize(Camera& camera)
{
	nlohmann::json* oldJson = m_pCurrentJson;
	nlohmann::json cameraJson;
	m_pCurrentJson = &cameraJson;

	cameraJson["fovYAngle"] = camera.fovYangle;
	cameraJson["zNear"] = camera.zNear;
	cameraJson["zFar"] = camera.zFar;

	(*oldJson)["Camera"] = cameraJson;
	m_pCurrentJson = oldJson;
}