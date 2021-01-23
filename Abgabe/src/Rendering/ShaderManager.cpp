#include "ShaderManager.h"

#include <fstream>
#include <sstream>

ShaderManager ShaderManager::s_instance;

ShaderManager::ShaderManager()
	:m_ShaderLookup()
{

}

ShaderManager::~ShaderManager()
{
	for (auto& element : m_ShaderLookup)
	{
		delete element.second;
	}
}

Shader* ShaderManager::GetShader(std::string& name)
{
	auto lookupIt = m_ShaderLookup.find(name);
	if (lookupIt == m_ShaderLookup.end())
	{
		std::cout << "Shader '" << name << "' not found!" << std::endl;
		return nullptr;
	}
	return lookupIt->second;
}

bool ShaderManager::RegisterShader(const char* sourcePath)
{
	std::ifstream filestream(sourcePath);

	//Check if file opens
	if (filestream.fail())
	{
		std::cout << "Error opening Shader File at: " << sourcePath << std::endl;
		return false;
	}

	//Check if file Contains name
	std::string tempstring;
	std::getline(filestream, tempstring, '\n');

	std::istringstream linestream(tempstring);
	linestream >> tempstring;
	if (!(tempstring == "name" || tempstring == "Name"))
	{
		std::cout << "Shader has no name. Location: " << sourcePath << std::endl;
		filestream.close();
		return false;
	}
	filestream.close();

	//Check if Shader already exists
	linestream >> tempstring;

	auto lookupIt = m_ShaderLookup.find(tempstring);
	if (lookupIt != m_ShaderLookup.end())
	{
		std::cout << "Shader '" << tempstring << "' already exists!" << std::endl;
		return false;
	}

	//Create and add shader to Lookup
	Shader* shader = new Shader(sourcePath);
	m_ShaderLookup.insert(std::make_pair(shader->GetName(), shader));
	return true;
}

