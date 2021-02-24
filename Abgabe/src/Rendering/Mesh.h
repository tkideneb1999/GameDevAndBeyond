#pragma once

#include <vector>

#include "GL/glew.h"
#include "glm/vec3.hpp"

#include "Vertex.h"
#include "Material.h"
#include "Transform.h"
#include "Camera.h"

#include "../Serialization/SceneArchive.h"

class MeshGUI;

class Mesh
{
private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::string m_modelPath;

	GLuint m_VAOHandle;
	GLuint m_VBOHandle;
	GLuint m_IBOHandle;

public:
	Material material;

private:
	inline void GenerateBuffers();
	inline void LoadMesh();
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh(const char* modelPath);
	Mesh();
	~Mesh();
	Mesh(const Mesh&);

	std::string& GetModelPath() { return m_modelPath; }

	void ChangeMesh(const char* modelPath);

	void SetMaterial(const char* materialPath);
	void SetMaterial(Material& newMaterial);

	unsigned int getIndicesCount() { return m_indices.size(); }

	GLuint getVAOHandle() { return m_VAOHandle; }
	GLuint getVBOHandle() { return m_VBOHandle; }
	GLuint getIBOHandle() { return m_IBOHandle; }

	void Serialize(SceneOutputArchive& outputArchive);

	friend class MeshGUI;
};