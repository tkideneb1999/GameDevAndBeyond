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

	GLuint m_VAOHandle;
	GLuint m_VBOHandle;
	GLuint m_IBOHandle;

public:
	Shader* shader;

private:
	inline void GenerateBuffers();
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh(const char* modelPath);
	Mesh();
	~Mesh();
	Mesh(const Mesh&);

	void SetShader(const char* shaderPath);

	unsigned int getIndicesCount() { return m_indices.size(); }

	GLuint getVAOHandle() { return m_VAOHandle; }
	GLuint getVBOHandle() { return m_VBOHandle; }
	GLuint getIBOHandle() { return m_IBOHandle; }
};