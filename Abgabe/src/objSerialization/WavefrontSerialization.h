#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

#include "../Rendering/Vertex.h"

namespace WavefrontSerialization
{

	void LoadWavefront(const char* path, std::vector<Vertex>& outVertexList, std::vector<unsigned int>& outIndicesList)
	{
		std::ifstream wfObj(path);

		if (wfObj.fail())
		{
			std::cerr << "Error Opening File" << std::endl;
		}

		std::string currentLine;

		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> texcoords;
		std::vector<glm::vec3> normals;

		std::unordered_map<std::string, unsigned int> indexMap;
		unsigned int uniqueVertexCount = 0;

		outVertexList.clear();
		outIndicesList.clear();

		while (std::getline(wfObj, currentLine, '\n'))
		{
			std::istringstream linestream(currentLine);
			std::string vertexDataType;
			linestream >> vertexDataType;

			//Extract vertex Positions
			if (vertexDataType == "v")
			{

				glm::vec3 ref = positions.emplace_back(0, 0, 0);

				linestream >> ref.x;
				linestream >> ref.y;
				linestream >> ref.z;

				std::cout << "VertexPosition detected, with Positions: x: " << ref.x << " y: " << ref.y << " z: " << ref.z << std::endl;
			}

			//Extract Texture Coordinates
			if (vertexDataType == "vt")
			{
				glm::vec2& ref = texcoords.emplace_back(0, 0);

				linestream >> ref.x;
				linestream >> ref.y;

				std::cout << "VertexUV detected, with Coordinates: x: " << ref.x << " y: " << ref.y << std::endl;
			}

			//Extract Normals
			if (vertexDataType == "vn")
			{
				glm::vec3& ref = normals.emplace_back(0, 0, 0);

				linestream >> ref.x;
				linestream >> ref.y;
				linestream >> ref.z;

				std::cout << "VertexNormal detected, with values: x: " << ref.x << " y: " << ref.y << " z: " << ref.z << std::endl;
			}

			//Extract Face indices
			if (vertexDataType == "f")
			{
				std::string indexString;

				for (int i = 0; i < 3; i++)
				{
					linestream >> indexString;
					std::istringstream indexStream(indexString);

					std::string tempString;

					auto it = indexMap.find(tempString);
					if (it == indexMap.end())
					{
						indexMap.insert(std::make_pair(tempString, uniqueVertexCount));
						uniqueVertexCount++;
					}

					//unoptimized vertex creation, creates duplicate vertices
					Vertex& vertexRef = outVertexList.emplace_back();

					std::getline(indexStream, tempString, '/');
					vertexRef.position = positions[(std::stoi(tempString) - 1)];


					std::getline(indexStream, tempString, '/');
					vertexRef.texcoord1 = texcoords[(std::stoi(tempString) - 1)];

					std::getline(indexStream, tempString, '/');
					vertexRef.normal = normals[(std::stoi(tempString) - 1)];

					outIndicesList.emplace_back((unsigned int)(outVertexList.size() - 1));
				}
			}
		}

		std::cout << "Vertex Count: " << outVertexList.size() << std::endl;
		std::cout << "Indices Count: " << outIndicesList.size() << std::endl;
		std::cout << "Unique Vertices Count: " << uniqueVertexCount + 1 << std::endl;

		wfObj.close();
	}
}