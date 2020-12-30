#pragma once

#include "entt/entt.hpp"

#include "Transform.h"
#include "Camera.h"
#include "Mesh.h"

class RenderSystem
{
public:
	void RenderSingle(Camera& camera, Transform& transform, Mesh& mesh);
	void Render(entt::registry& registry);
};