#pragma once

#include "glm/mat4x4.hpp"
#include "glm/gtc/quaternion.hpp"
class Transform
{
public:
	glm::mat4x4 transform;
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	Transform();
	Transform(const glm::vec3 initPosition, const glm::quat initRotation, const glm::vec3 initScale);

	void SetPosition(const glm::vec3 newPosition);
	void SetRotation(const glm::quat newRotation);
	void SetScale(const glm::vec3 newScale);
	void SetTransform(const glm::vec3 newPosition, const glm::vec3 newRotation, const glm::vec3 newScale);
	void SetTransform(const glm::vec3 newPosition, const glm::quat newRotation, const glm::vec3 newScale);
	void RotateAroundAxis(const glm::vec3& axis, const float& angleRadians);

private:
	void ConstructMatrix();
};