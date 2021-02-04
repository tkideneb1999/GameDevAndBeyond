#include "Mesh.h"

#include "../Serialization/WavefrontSerialization.h"

#define DEBUGBREAKLINE std::cout << "----------------------" << std::endl

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	:material()
{
	DEBUGBREAKLINE;
	std::cout << "Creating Mesh from existing Data" << std::endl;
	m_vertices = vertices;
	m_indices = indices;
	GenerateBuffers();
}

Mesh::Mesh(const char* modelPath)
	:material()
{
	DEBUGBREAKLINE;
	std::cout << "Loading Model from:" << std::endl;
	std::cout << modelPath << std::endl;
	WavefrontSerialization::LoadWavefront(modelPath, m_vertices, m_indices);
	GenerateBuffers();
}

Mesh::Mesh()
	:material()
{
	DEBUGBREAKLINE;
	std::cout << "Loading Model from:" << std::endl;
	std::cout << "../resources/plane.obj" << std::endl;
	WavefrontSerialization::LoadWavefront("../resources/plane.obj", m_vertices, m_indices);
	GenerateBuffers();
}

Mesh::Mesh(const Mesh& mesh)
	:material(mesh.material),
	m_vertices(mesh.m_vertices), m_indices(mesh.m_indices)
{
	DEBUGBREAKLINE;
	std::cout << "Copying Mesh Data" << std::endl;
	std::cout << "Vertex Count: " << m_vertices.size() << std::endl;
	std::cout << "Indices Count: " << m_indices.size() << std::endl;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	DEBUGBREAKLINE;
	std::cout << "Deleting Mesh" << std::endl;
	//Disable Generic Vertex Attributes
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	//Delete Index/Vertex Buffer
	glDeleteBuffers(1, &m_VBOHandle);
	glDeleteBuffers(1, &m_IBOHandle);

	//Delete VAO
	glDeleteVertexArrays(1, &m_VAOHandle);
}

void Mesh::SetMaterial(const char* materialPath)
{
	material = Material(materialPath);
}

void Mesh::SetMaterial(Material& newMaterial)
{
	material = newMaterial;
}

inline void Mesh::GenerateBuffers()
{
	//Generate & Bind VAO
	glGenVertexArrays(1, &m_VAOHandle);
	glBindVertexArray(m_VAOHandle);

	//Generate & Bind Vertex Buffer to VAO
	glGenBuffers(1, &m_VBOHandle);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

	//Enable Generic Vertex Attributes (0 = Position, 1 = Normal, 2 = Color, 3 = TexCoord1)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)24);

	//Create & Bind Index Buffer
	glGenBuffers(1, &m_IBOHandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBOHandle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

	//Unbind VAO
	glBindVertexArray(0);

	//Unbind Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}