#include "Entity.h"

#include "Rendering/Transform.h"
#include "Rendering/Mesh.h"
#include "Rendering/Camera.h"

Entity::Entity(entt::entity entityID, Scene& scene)
	:entity(entityID), name("Entity"), m_pScene(&scene)
{}

Entity::Entity(entt::entity entityID, const char* objectName, Scene& scene)
	:entity(entityID), name(objectName), m_pScene(&scene)
{}

void Entity::Serialize(SceneOutputArchive& outputArchive)
{
	outputArchive.Serialize(name, "EntityName");
	unsigned long addedComponents = 0;
	if (HasComponent<Transform>())
	{
		addedComponents |= 1UL << 0;
	}
	if (HasComponent<Mesh>())
	{
		addedComponents |= 1UL << 1;
	}
	if (HasComponent<Camera>())
	{
		addedComponents |= 1UL << 2;
	}

	outputArchive.Serialize(addedComponents, "AddedComponents");

	if ((addedComponents >> 0) & 1U)
	{
		auto& transform = GetComponent<Transform>();
		outputArchive.Serialize(transform, "Transform");
	}

	if ((addedComponents >> 1) & 1U)
	{
		auto& mesh = GetComponent<Mesh>();
		outputArchive.Serialize(mesh, "Mesh");
	}

	if ((addedComponents >> 2) & 1U)
	{
		auto& camera = GetComponent<Camera>();
		outputArchive.Serialize(camera, "Camera");
	}
}