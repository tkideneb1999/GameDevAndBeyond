#pragma once

#include "glm/mat4x4.hpp"
#include "glm/gtc/quaternion.hpp"

#include "../Serialization/SceneArchive.h"

class TransformGUI;

class Transform
{
private:
	glm::mat4x4 m_ModelMatrix;
public:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;
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

private:
	void ConstructMatrix();

	friend class TransformGUI;

public:
	void Serialize(SceneOutputArchive& outputArchive);
	void Serialize(SceneInputArchive& inputArchive);
};