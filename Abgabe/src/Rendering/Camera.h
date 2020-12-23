#pragma once

#include "glm/mat4x4.hpp"

#include "Transform.h"

class Camera
{
public:
	glm::mat4x4 projection;
	Transform transform;

	
};
