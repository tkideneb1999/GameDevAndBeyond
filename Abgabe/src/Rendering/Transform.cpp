#include "Transform.h"

#include "glm/gtc/matrix_transform.hpp"

Transform::Transform()
	:position(0.0f, 0.0f, 0.0f), rotation(), scale(1.0f, 1.0f, 1.0f)
{
	ConstructMatrix();
}

Transform::Transform(glm::vec3 initPosition, glm::quat initRotation, glm::vec3 initScale)
	:position(initPosition), rotation(initRotation), scale(initScale)
{
	ConstructMatrix();
}

void Transform::SetPosition(const glm::vec3 newPosition)
{
	position = newPosition;
	ConstructMatrix();
}

void Transform::SetRotation(glm::quat newRotation)
{
	rotation = newRotation;
	ConstructMatrix();
}

void Transform::SetScale(const glm::vec3 newScale)
{
	scale = newScale;
	ConstructMatrix();
}

void Transform::SetTransform(const glm::vec3 newPosition, const glm::vec3 newRotation, const glm::vec3 newScale)
{
	position = newPosition;
	scale = newScale;

	rotation = glm::rotate(glm::quat()  , newRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	rotation = glm::rotate(rotation   , newRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotation = glm::rotate(rotation   , newRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	ConstructMatrix();
}

void Transform::SetTransform(const glm::vec3 newPosition, const glm::quat newRotation, const glm::vec3 newScale)
{
	position = newPosition;
	rotation = newRotation;
	scale = newScale;

	ConstructMatrix();
}

void Transform::RotateAroundAxis(const glm::vec3& axis,const float& angleRadians)
{
	m_ModelMatrix = glm::rotate(m_ModelMatrix, angleRadians, axis);
}

void Transform::ConstructMatrix()
{
	m_ModelMatrix = glm::translate(glm::mat4_cast(rotation) * glm::scale(glm::mat4(1.0), scale), position);
}

void Transform::Serialize(SceneOutputArchive& outputArchive)
{
	outputArchive.Serialize(position, "pos");
	outputArchive.Serialize(rotation, "rot");
	outputArchive.Serialize(scale, "scl");
}