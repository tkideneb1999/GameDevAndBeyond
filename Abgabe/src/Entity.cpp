#include "Entity.h"

int Entity::entityIDCount = 0;

Entity::Entity()
{
	entityID = entityIDCount;
	entityIDCount++;
}

Entity::~Entity()
{
	
}
