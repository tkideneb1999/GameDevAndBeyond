#pragma once

#include "glm/mat4x4.hpp"

#include "Transform.h"

class Camera
{
private:
	glm::mat4x4 m_Projection;

public:
	Camera(float aspectRatio);
	Camera(float fovYangle, float aspectRatio, float zNear, float zFar);
	Camera(const Camera& camera) = default;

	void SetCameraData(float fovY, float aspectRatio, float zNear, float zFar);

	inline glm::mat4x4 ViewMatrix(Transform cameraTransform)
	{
		return glm::inverse(cameraTransform.GetModelMatrix());
	}

	glm::mat4x4 Projection()
	{
		return m_Projection;
	}
};
