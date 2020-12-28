#include "Transform.h"

#include "glm/gtc/matrix_transform.hpp"

Transform::Transform()
	:m_Position(0.0f, 0.0f, 0.0f), m_Rotation(), m_Scale(1.0f, 1.0f, 1.0f)
{
	ConstructMatrix();
}

Transform::Transform(glm::vec3 initPosition, glm::quat initRotation, glm::vec3 initScale)
	:m_Position(initPosition), m_Rotation(initRotation), m_Scale(initScale)
{
	ConstructMatrix();
}

void Transform::SetPosition(const glm::vec3 newPosition)
{
	m_Position = newPosition;
	ConstructMatrix();
}

void Transform::SetRotation(glm::quat newRotation)
{
	m_Rotation = newRotation;
	ConstructMatrix();
}

void Transform::SetScale(const glm::vec3 newScale)
{
	m_Scale = newScale;
	ConstructMatrix();
}

void Transform::SetTransform(const glm::vec3 newPosition, const glm::vec3 newRotation, const glm::vec3 newScale)
{
	m_Position = newPosition;
	m_Scale = newScale;

	m_Rotation = glm::rotate(glm::quat()  , newRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	m_Rotation = glm::rotate(m_Rotation   , newRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	m_Rotation = glm::rotate(m_Rotation   , newRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	ConstructMatrix();
}

void Transform::SetTransform(const glm::vec3 newPosition, const glm::quat newRotation, const glm::vec3 newScale)
{
	m_Position = newPosition;
	m_Rotation = newRotation;
	m_Scale = newScale;

	ConstructMatrix();
}

void Transform::RotateAroundAxis(const glm::vec3& axis,const float& angleRadians)
{
	m_ModelMatrix = glm::rotate(m_ModelMatrix, angleRadians, axis);
}

void Transform::ConstructMatrix()
{
	m_ModelMatrix = glm::translate(glm::mat4_cast(m_Rotation) * glm::scale(glm::mat4(1.0), m_Scale), m_Position);
}