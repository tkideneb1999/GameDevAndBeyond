#include "Material.h"

#include <filesystem>

#include "../Serialization/MaterialArchive.h"
#include "ShaderManager.h"

Material::Material()
{
	std::string shaderName("Default");
	m_pShader = ShaderManager::Get().GetShader(shaderName);
	GetUniformsFromShader();
}

Material::Material(const char* filePath)
	:m_Location(filePath)
{
	std::string shaderName;
	LoadMaterial(shaderName);
	//Get Shader
	m_pShader = ShaderManager::Get().GetShader(shaderName);
	//Collect non Serialized Uniforms
	GetUniformsFromShader();
}

Material::Material(const Material& mat)
	:m_iUniforms(mat.m_iUniforms), m_fUniforms(mat.m_fUniforms), m_v2Uniforms(mat.m_v2Uniforms), 
	m_v3Uniforms(mat.m_v3Uniforms), m_v4Uniforms(mat.m_v4Uniforms), m_m4Uniforms(mat.m_m4Uniforms)
{
	std::string shaderName = mat.m_pShader->GetName();
	m_pShader = ShaderManager::Get().GetShader(shaderName);
}

Material::~Material()
{

}

void Material::SetUniform(const char* name, float value)
{
	auto it = m_fUniforms.find(name);
	if (it == m_fUniforms.end())
	{
		std::cout << "Uniform '" << name << "' does not exist" << std::endl;
		return;
	}
	it->second = value;
}
void Material::SetUniform(const char* name, glm::vec2 value)
{
	auto it = m_v2Uniforms.find(name);
	if (it == m_v2Uniforms.end())
	{
		std::cout << "Uniform '" << name << "' does not exist" << std::endl;
		return;
	}
	it->second = value;
}
void Material::SetUniform(const char* name, glm::vec3 value)
{
	auto it = m_v3Uniforms.find(name);
	if (it == m_v3Uniforms.end())
	{
		std::cout << "Uniform '" << name << "' does not exist" << std::endl;
		return;
	}
	it->second = value;
}
void Material::SetUniform(const char* name, glm::vec4 value)
{
	auto it = m_v4Uniforms.find(name);
	if (it == m_v4Uniforms.end())
	{
		std::cout << "Uniform '" << name << "' does not exist" << std::endl;
		return;
	}
	it->second = value;
}
void Material::SetUniform(const char* name, glm::mat4x4 value)
{
	auto it = m_m4Uniforms.find(name);
	if (it == m_m4Uniforms.end())
	{
		if (name = "u_ITM")
			return;
		std::cout << "Uniform '" << name << "' does not exist" << std::endl;
		return;
	}
	it->second = value;
}

void Material::TansferUniforms()
{
	for (auto& element : m_iUniforms)
	{
		m_pShader->SetUniform(element.first.c_str(), element.second);
	}
	for (auto& element : m_fUniforms)
	{
		m_pShader->SetUniform(element.first.c_str(), element.second);
	}
	for (auto& element : m_v2Uniforms)
	{
		m_pShader->SetUniform(element.first.c_str(), element.second);
	}
	for (auto& element : m_v3Uniforms)
	{
		m_pShader->SetUniform(element.first.c_str(), element.second);
	}
	for (auto& element : m_v4Uniforms)
	{
		m_pShader->SetUniform(element.first.c_str(), element.second);
	}
	for (auto& element : m_m4Uniforms)
	{
		m_pShader->SetUniform(element.first.c_str(), element.second);
	}
}

void Material::SetShader(std::string shaderName)
{
	m_iUniforms.clear();
	m_fUniforms.clear();
	m_v2Uniforms.clear();
	m_v3Uniforms.clear();
	m_v4Uniforms.clear();
	m_m4Uniforms.clear();

	m_pShader = ShaderManager::Get().GetShader(shaderName);
	GetUniformsFromShader();
}

void Material::GetUniformsFromShader()
{
	auto& uniformTypeMap = m_pShader->GetUniformTypeMap();
	for (auto& uniformType : uniformTypeMap)
	{
		switch (uniformType.second)
		{
		case GL_FLOAT:
			{
				auto uniformIt = m_fUniforms.find(uniformType.first);
				if (uniformIt == m_fUniforms.end())
					m_fUniforms.insert(std::make_pair(uniformType.first, 0.0f));
			}
			break;
		
		case GL_INT:
			{
				auto uniformIt = m_iUniforms.find(uniformType.first);
				if (uniformIt == m_iUniforms.end())
					m_iUniforms.insert(std::make_pair(uniformType.first, 0));
			}
			break;

		case GL_FLOAT_VEC2:
			{
				auto uniformIt = m_v2Uniforms.find(uniformType.first);
				if (uniformIt == m_v2Uniforms.end())
					m_v2Uniforms.insert(std::make_pair(uniformType.first, glm::vec2(0.0f, 0.0f)));
			}
			break;

		case GL_FLOAT_VEC3:
			{
				auto uniformIt = m_v3Uniforms.find(uniformType.first);
				if (uniformIt == m_v3Uniforms.end())
					m_v3Uniforms.insert(std::make_pair(uniformType.first, glm::vec3(0.0f, 0.0f, 0.0f)));
			}
			break;

		case GL_FLOAT_VEC4:
			{
				auto uniformIt = m_v4Uniforms.find(uniformType.first);
				if (uniformIt == m_v4Uniforms.end())
					m_v4Uniforms.insert(std::make_pair(uniformType.first, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)));
			}
			break;
		case GL_FLOAT_MAT4:
			{
				auto uniformIt = m_m4Uniforms.find(uniformType.first);
				if (uniformIt == m_m4Uniforms.end())
					m_m4Uniforms.insert(std::make_pair(uniformType.first, glm::mat4(1.0f)));
			}
			break;
		}
	}
}

void Material::LoadMaterial(std::string& outShaderName)
{
	std::filesystem::path modelPath(m_Location);
	std::string sEnding = modelPath.extension().generic_string();
	if (sEnding == ".mat")
	{
		MaterialSerialization::LoadMaterial(m_Location.c_str(), outShaderName, m_iUniforms, m_fUniforms, m_v2Uniforms, m_v3Uniforms, m_v4Uniforms);		
	}
	else
	{
		std::cout << "Not a valid Material! Loading Default Material" << std::endl;
		outShaderName = "Default";
	}
}

void Material::SerializeMaterial(const char* filePath)
{
	m_Location = filePath;
	std::string shaderName = m_pShader->GetName();
	MaterialSerialization::MaterialOutputArchive archive(m_Location, shaderName);
	for (auto& uniform : m_iUniforms)
	{
		archive.Serialize(uniform.second, uniform.first);
	}

	for (auto& uniform : m_fUniforms)
	{
		archive.Serialize(uniform.second, uniform.first);
	}

	for (auto& uniform : m_v2Uniforms)
	{
		archive.Serialize(uniform.second, uniform.first);
	}

	for (auto& uniform : m_v3Uniforms)
	{
		archive.Serialize(uniform.second, uniform.first);
	}

	for (auto& uniform : m_v4Uniforms)
	{
		archive.Serialize(uniform.second, uniform.first);
	}
}