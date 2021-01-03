#pragma once

#include "entt/entt.hpp"

#include "Transform.h"
#include "Camera.h"
#include "Mesh.h"

class RenderSystem
{
public:
	void RenderSingle(Camera& camera, Transform& camtransform, Mesh& mesh, Transform& meshTransform);
	void Render(entt::registry& registry);
};