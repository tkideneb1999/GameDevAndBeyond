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

public:
	Transform transform;
	Shader shader;

	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	Mesh(const char* modelPath);

	void SetShader(const char* vertShaderPath, const char* fragShaderPath);
	
	void DrawMesh(Camera camera);
};