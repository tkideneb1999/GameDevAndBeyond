#pragma once

#include <vector>

#include "GL/glew.h"
#include "glm/vec3.hpp"

#include "Vertex.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

class Mesh
{
private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;

	glm::mat4x4 m_MVP;
	glm::mat4x4 m_ITM;

	GLuint m_VAOHandle;
	GLuint m_VBOHandle;
	GLuint m_IBOHandle;

public:
	Transform transform;
	Shader* shader;

private:
	inline void GenerateBuffers();
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh(const char* modelPath);
	~Mesh();

	void SetShader(const char* vertShaderPath, const char* fragShaderPath);
	
	void DrawMesh(Camera& camera);
};