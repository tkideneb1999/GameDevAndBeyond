#include "Mesh.h"

#include "../objSerialization/WavefrontSerialization.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	:shader(new Shader()), transform()
{
	m_vertices = vertices;
	m_indices = indices;
	GenerateBuffers();
}

Mesh::Mesh(const char* modelPath)
	:shader(new Shader()), transform()
{
	std::cout << "----------------------" << std::endl;
	std::cout << "Loading Model" << std::endl;
	WavefrontSerialization::LoadWavefront(modelPath, m_vertices, m_indices);
	GenerateBuffers();
}

Mesh::~Mesh()
{
	std::cout << "----------------------" << std::endl;
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

	delete shader;
}

void Mesh::SetShader(const char* vertShaderPath, const char* fragShaderPath)
{
	delete shader;
	shader = new Shader(vertShaderPath, fragShaderPath);
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
}

void Mesh::DrawMesh(Camera& camera)
{
	glBindVertexArray(m_VAOHandle);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOHandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBOHandle);
	shader->EnableShader();

	//Update Matrices
	m_MVP = camera.Projection() * (camera.ViewMatrix() * transform.transform);
	m_ITM = glm::transpose(glm::inverse(transform.transform));

	//Set Uniform Matrices
	shader->SetMatrix4x4("u_MVP", m_MVP);
	shader->SetMatrix4x4("u_ITM", m_ITM);

	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

	shader->DisableShader();
}