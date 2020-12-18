#pragma once
#include "Component.h"
#include <unordered_map>

class Entity
{
public:
	typedef int typeID;
	typedef int componentIndex;

	Entity();

	~Entity();

	template<typename C>
	void AddComponent()
	{
		int index = C.CreateComponent(entityID);
	
		//Add Pointer to list
		//m_pComponents.insert(pComponent);
	}
	
	template<typename C>
	void RemoveComponent()
	{
		C* pComponent = C.RemoveComponent(entityID);
	
		//Remove pointer from list
		m_pComponents.find(pComponent);
		m_pComponents.erase();
	}
	
	template<typename C>
	C* GetComponent()
	{
		
	}

private:
	int entityID;
	std::unordered_map<typeID, componentIndex> m_pComponents;
	static int entityIDCount;
};