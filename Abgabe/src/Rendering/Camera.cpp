#include "Camera.h"

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"

Camera::Camera()
	:fovYangle(90.0f), aspectRatio(1920.0f/1080.0f), zNear(0.01f), zFar(100.0f)
{
	ApplyCameraData();
}

Camera::Camera(float aspectRatio)
	:fovYangle(90.0f), aspectRatio(aspectRatio), zNear(0.01f), zFar(100.0f)
{
	ApplyCameraData();
}

Camera::Camera(float fovYangle, float aspectRatio, float zNear, float zFar)
	: fovYangle(fovYangle), aspectRatio(aspectRatio), zNear(zNear), zFar(zFar)
{
	ApplyCameraData();
}

void Camera::SetCameraData(float fovY, float aspectRatio, float zNear, float zFar)
{
	fovYangle = fovY;
	aspectRatio = aspectRatio;
	zNear = zNear;
	zFar = zFar;
	ApplyCameraData();
}

void Camera::ApplyCameraData()
{
	m_Projection = glm::perspective(glm::radians(fovYangle), aspectRatio, zNear, zFar);
}

void Camera::Serialize(SceneOutputArchive& outputArchive)
{
	outputArchive.Serialize(fovYangle, "fovY");
	outputArchive.Serialize(aspectRatio, "aspectRation");
	outputArchive.Serialize(zNear, "zNear");
	outputArchive.Serialize(zFar, "zFar");
}

void Camera::Serialize(SceneInputArchive& inputArchive)
{
	inputArchive.Serialize(fovYangle, "fovY");
	inputArchive.Serialize(aspectRatio, "aspectRation");
	inputArchive.Serialize(zNear, "zNear");
	inputArchive.Serialize(zFar, "zFar");

	ApplyCameraData();
}