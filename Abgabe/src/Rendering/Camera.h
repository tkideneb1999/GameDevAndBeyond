#pragma once

#include "glm/mat4x4.hpp"

#include "Transform.h"

class Camera
{
private:
	glm::mat4x4 m_Projection;

public:
	Transform transform;
	Camera(float aspectRatio);
	Camera(float fovYangle, float aspectRatio, float zNear, float zFar);

	void SetCameraData(float fovY, float aspectRatio, float zNear, float zFar);

	inline glm::mat4x4 ViewMatrix()
	{
		return glm::inverse(transform.transform);
	}

	glm::mat4x4 Projection()
	{
		return m_Projection;
	}
};
