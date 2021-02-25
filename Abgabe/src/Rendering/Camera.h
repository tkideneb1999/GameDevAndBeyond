#pragma once

#include "glm/mat4x4.hpp"

#include "Transform.h"
#include "../Serialization/SceneArchive.h"

class CameraGUI;

class Camera
{
public:
	float fovYangle;
	float aspectRatio;
	float zNear;
	float zFar;
private:
	glm::mat4x4 m_Projection;
public:
	Camera();
	Camera(float aspectRatio);
	Camera(float fovYangle, float aspectRatio, float zNear, float zFar);
	Camera(const Camera& camera) = default;

	void SetCameraData(float fovY, float aspectRatio, float zNear, float zFar);
	void ApplyCameraData();

	inline glm::mat4x4 ViewMatrix(Transform cameraTransform)
	{
		return glm::inverse(cameraTransform.GetModelMatrix());
	}

	glm::mat4x4 Projection()
	{
		return m_Projection;
	}

	void Serialize(SceneOutputArchive& outputArchive);
	void Serialize(SceneInputArchive& inputArchive);

	friend class CameraGUI;
};
