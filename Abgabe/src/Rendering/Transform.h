#pragma once

#include "glm/mat4x4.hpp"
#include "glm/gtc/quaternion.hpp"

class TransformGUI;

class Transform
{
private:
	glm::mat4x4 m_ModelMatrix;
	glm::vec3 m_Position;
	glm::quat m_Rotation;
	glm::vec3 m_Scale;
public:
	Transform();
	Transform(const Transform& transform) = default;
	Transform(const glm::vec3 initPosition, const glm::quat initRotation, const glm::vec3 initScale);

	void SetPosition(const glm::vec3 newPosition);
	void SetRotation(const glm::quat newRotation);
	void SetScale(const glm::vec3 newScale);
	void SetTransform(const glm::vec3 newPosition, const glm::vec3 newRotation, const glm::vec3 newScale);
	void SetTransform(const glm::vec3 newPosition, const glm::quat newRotation, const glm::vec3 newScale);
	void RotateAroundAxis(const glm::vec3& axis, const float& angleRadians);

	glm::mat4x4 GetModelMatrix() { return m_ModelMatrix; }

	glm::vec3 GetPosition() { return m_Position; }
	glm::quat GetRotation() { return m_Rotation; }
	glm::vec3 GetScale() { return m_Scale; }

private:
	void ConstructMatrix();

	friend class TransformGUI;
};