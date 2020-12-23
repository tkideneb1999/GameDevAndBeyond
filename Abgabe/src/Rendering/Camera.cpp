#include "Camera.h"

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(float aspectRatio)
{
	m_Projection = glm::perspective(90.0f, aspectRatio, 0.01f, 100.0f);
}

Camera::Camera(float fovYangle, float aspectRatio, float zNear, float zFar)
{
	m_Projection = glm::perspective(glm::radians(fovYangle), aspectRatio, zNear, zFar);
}

void Camera::SetCameraData(float fovY, float aspectRatio, float zNear, float zFar)
{
	m_Projection = glm::perspective(fovY, aspectRatio, zNear, zFar);
}