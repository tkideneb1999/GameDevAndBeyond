#include "Mesh.h"

#include <filesystem>

#include "../Serialization/WavefrontSerialization.h"

#define DEBUGBREAKLINE std::cout << "----------------------" << std::endl

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	:material(), m_modelPath("Cache")
{
	DEBUGBREAKLINE;
	std::cout << "Creating Mesh from existing Data" << std::endl;
	m_vertices = vertices;
	m_indices = indices;
	GenerateBuffers();
}

Mesh::Mesh(const char* initModelPath)
	:material(), m_modelPath(initModelPath)
{
	DEBUGBREAKLINE;
	std::cout << "Loading Model from:" << std::endl;
	std::cout << m_modelPath << std::endl;
	LoadMesh();
	GenerateBuffers();
}

Mesh::Mesh()
	:material(), m_modelPath("../resources/plane.obj")
{
	DEBUGBREAKLINE;
	std::cout << "Loading Model from:" << std::endl;
	std::cout << m_modelPath << std::endl;
	LoadMesh();
	GenerateBuffers();
}

Mesh::Mesh(const Mesh& mesh)
	:material(mesh.material),
	m_vertices(mesh.m_vertices), m_indices(mesh.m_indices),
	m_modelPath(mesh.m_modelPath)
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

void Mesh::ChangeMesh(const char* modelPath)
{
	m_modelPath = modelPath;
	glDeleteBuffers(1, &m_VBOHandle);
	glDeleteBuffers(1, &m_IBOHandle);
	glDeleteVertexArrays(1, &m_VAOHandle);

	LoadMesh();
	DEBUGBREAKLINE;
	std::cout << "Changed Model" << std::endl;
	std::cout << "Vertex Count: " << m_vertices.size() << std::endl;
	std::cout << "Indices Count: " << m_indices.size() << std::endl;
	GenerateBuffers();
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

inline void Mesh::LoadMesh()
{
	std::filesystem::path modelPath(m_modelPath);
	std::string sEnding = modelPath.extension().generic_string();
	if (sEnding == ".obj")
	{
		WavefrontSerialization::LoadWavefront(m_modelPath.c_str(), m_vertices, m_indices);
	}
	else
	{
		std::cout << "File Extension not recognized" << std::endl;
	}
}

void Mesh::Serialize(SceneOutputArchive& outputArchive)
{
	outputArchive.Serialize(m_modelPath, "modelPath");
	bool materialSerialized = material.IsSerialized();
	outputArchive.Serialize(materialSerialized, "matSerialized");
	if (material.IsSerialized())
	{
		outputArchive.Serialize(material.GetMaterialLocation(), "materialPath");
	}
	else
	{
		std::string loc("");
		outputArchive.Serialize(loc, "materialPath");
	}

}

void Mesh::Serialize(SceneInputArchive& inputArchive)
{
	inputArchive.Serialize(m_modelPath, "modelPath");
	bool materialSerialized = material.IsSerialized();
	inputArchive.Serialize(materialSerialized, "matSerialized");
	if (materialSerialized)
	{
		std::string materialPath;
		inputArchive.Serialize(materialPath, "materialPath");
		material = Material(materialPath.c_str());
	}
	else
	{
		material = Material();
	}

	glDeleteBuffers(1, &m_VBOHandle);
	glDeleteBuffers(1, &m_IBOHandle);
	glDeleteVertexArrays(1, &m_VAOHandle);

	LoadMesh();
	DEBUGBREAKLINE;
	std::cout << "Loaded Model from Serialized Content" << std::endl;
	std::cout << "Vertex Count: " << m_vertices.size() << std::endl;
	std::cout << "Indices Count: " << m_indices.size() << std::endl;
	GenerateBuffers();
}