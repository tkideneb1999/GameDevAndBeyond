#include "Entity.h"

#include "Rendering/Transform.h"
#include "Rendering/Mesh.h"
#include "Rendering/Camera.h"

Entity::Entity(Scene& scene) noexcept
	:name("Entity"), m_pScene(&scene)
{
	entityHandle = m_pScene->m_registry.create();
}

Entity::Entity(const char* objectName, Scene& scene) noexcept
	:name(objectName), m_pScene(&scene)
{
	entityHandle = m_pScene->m_registry.create();
}

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

void Entity::Serialize(SceneInputArchive& inputArchive)
{
	inputArchive.Serialize(name, "EntityName");
	unsigned long addedComponents = 0;
	inputArchive.Serialize(addedComponents, "AddedComponents");

	if ((addedComponents >> 0) & 1U)
	{
		auto& transform = AddComponent<Transform>();
		inputArchive.Serialize(transform, "Transform");
	}

	if ((addedComponents >> 1) & 1U)
	{
		auto& mesh = AddComponent<Mesh>();
		inputArchive.Serialize(mesh, "Mesh");
	}

	if ((addedComponents >> 2) & 1U)
	{
		auto& camera = AddComponent<Camera>();
		inputArchive.Serialize(camera, "Camera");
	}
}