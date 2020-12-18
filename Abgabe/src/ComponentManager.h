#pragma once
#include <unordered_map>
#include <vector>

#include "Component.h"

class ComponentManager
{
public:
	typedef int ComponentID;
private:
	static ComponentManager m_instance;
	static int componentTypeID;
	std::unordered_map<ComponentID, std::vector<Component>> m_ComponentMap;
public:

	template<typename C>
	static int GetID()
	{
		static int ID = componentTypeID++;
		return ID;
	}
	void AddComponent();
	void RemoveComponent();
};
