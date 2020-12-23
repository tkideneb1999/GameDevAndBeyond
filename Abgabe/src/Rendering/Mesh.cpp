#include "Mesh.h"

#include "../objSerialization/WavefrontSerialization.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	m_vertices = vertices;
	m_indices = indices;
	transform = Transform();
	shader = Shader();
}

Mesh::Mesh(const char* modelPath)
{
	WavefrontSerialization::LoadWavefront(modelPath, m_vertices, m_indices);
	transform = Transform();
	shader = Shader();
}

void Mesh::SetShader(const char* vertShaderPath, const char* fragShaderPath)
{
	shader = Shader(vertShaderPath, fragShaderPath);
}

void Mesh::DrawMesh(Camera camera)
{

}