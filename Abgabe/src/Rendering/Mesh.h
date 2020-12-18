#pragma once

#include <vector>

#include "Vertex.h"

class Mesh
{
private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};