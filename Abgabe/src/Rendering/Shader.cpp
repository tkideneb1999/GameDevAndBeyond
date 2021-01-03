#include "Shader.h"

#include <sstream>

Shader::Shader(const char* filePath)
	:m_ShaderLocation(filePath)
{
	std::cout << "----------------------" << std::endl;
	std::cout << "Creating Shader" << std::endl;
	CreateShaderProgram(m_ShaderLocation);
}

Shader::Shader()
	:m_ShaderLocation("../Abgabe/resources/Shaders/Default.shader")
{
	std::cout << "----------------------" << std::endl;
	std::cout << "Creating Shader" << std::endl;
	CreateShaderProgram(m_ShaderLocation);
}

Shader::~Shader()
{
	std::cout << "----------------------" << std::endl;
	std::cout << "Deleting Shader" << std::endl;
	glDeleteProgram(m_ShaderProgramHandle);
}

Shader::Shader(const Shader& shader)
	:m_ShaderLocation(shader.m_ShaderLocation), m_UniformMap(shader.m_UniformMap)
{
	std::cout << "----------------------" << std::endl;
	std::cout << "Copying Shader" << std::endl;
	CreateShaderProgram(m_ShaderLocation);
}

void Shader::EnableShader()
{
#ifdef _DEBUG
	glValidateProgram(m_ShaderProgramHandle);
#endif
	glUseProgram(m_ShaderProgramHandle);
}

void Shader::DisableShader()
{
	glUseProgram(0);
}

void Shader::LoadSource(const char* filePath, std::string& outVertSource, std::string& outFragSource)
{
	std::ifstream fileStream(filePath);

	if (fileStream.fail())
	{
		std::cerr << "Error opening Shader file at: " << filePath << std::endl;
	}
	
	bool isVertSource = false;
	std::string fileContent;
	std::string tempString;
	std::getline(fileStream, tempString, '\n');

	std::istringstream nameStream(tempString);
	nameStream >> tempString;
	if (tempString == "name" || tempString == "Name")
	{
		nameStream >> m_Name;
	}

	while (std::getline(fileStream, tempString, '\n'))
	{
		if (tempString == "#vert")
		{
			isVertSource = true;
			continue;
		}
		else if (tempString == "#frag")
		{
			isVertSource = false;
			continue;
		}

		if (isVertSource)
		{
			outVertSource += tempString;
			outVertSource += '\n';
		}
		else
		{
			outFragSource += tempString;
			outFragSource += '\n';
		}

		fileContent += '\n';


	}
}

void Shader::CacheAllUniforms()
{
	//Get amount of used Uniforms in Shader
	GLint numActiveUniforms;
	glGetProgramiv(m_ShaderProgramHandle, GL_ACTIVE_UNIFORMS, &numActiveUniforms);
	if (numActiveUniforms == 0) return;

	//Get Length of longest Uniform Variable
	GLint uniformsMaxLength;
	glGetProgramiv(m_ShaderProgramHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformsMaxLength);
	
	//Get individual Uniforms & Cache them
	GLenum type;
	GLint size = 0;
	std::vector<GLchar> nameData(uniformsMaxLength);
	GLsizei length;

	for (int i = 0; i < numActiveUniforms; i++)
	{
		glGetActiveUniform(m_ShaderProgramHandle, i, uniformsMaxLength, &length, &size, &type, &nameData[0]);
		std::string name((char*)&nameData[0]);
		CacheUniformLocation(name.c_str());
		m_UniformTypeMap.insert(std::make_pair(name.c_str(), type));
	}
}

GLuint Shader::CreateShader(const GLchar* source, GLenum shaderType)
{

	GLuint shaderHandle = glCreateShader(shaderType);
	
	GLint sourceLength = strlen(source);

#ifdef _DEBUG
	switch (shaderType)
	{
	case GL_VERTEX_SHADER:
		std::cout << "Compiling Vertex Shader from: " << m_ShaderLocation << std::endl;
		break;
	case GL_FRAGMENT_SHADER:
		std::cout << "Compiling Fragment Shader from: " << m_ShaderLocation << std::endl;
		break;
	}
		//std::cout << "Source:" << std::endl;
		//std::cout << source << std::endl;
		//std::cout << "---" << std::endl;
#endif

	glShaderSource(shaderHandle, 1, &source, &sourceLength);
	glCompileShader(shaderHandle);
	delete[] source;
#ifdef _DEBUG
	CheckShaderCompilationResult(shaderHandle);
#endif

	return shaderHandle;
}

GLchar* Shader::CopyToGLchar(std::string& source)
{
	GLchar* fragSource = new GLchar[source.length() + 1];
	source.copy(fragSource, source.length());
	fragSource[source.length()] = '\0';
	return fragSource;
}

void Shader::CreateShaderProgram(const char* filePath)
{
	m_ShaderProgramHandle = glCreateProgram();

	std::string vertSourceStdString;
	std::string fragSourceStdString;

	LoadSource(filePath, vertSourceStdString, fragSourceStdString);

	const GLchar* vertSource = CopyToGLchar(vertSourceStdString);
	const GLchar* fragSource = CopyToGLchar(fragSourceStdString);

	GLuint vertShader = CreateShader(vertSource, GL_VERTEX_SHADER);
	GLuint fragShader = CreateShader(fragSource, GL_FRAGMENT_SHADER);

	glAttachShader(m_ShaderProgramHandle, vertShader);
	glAttachShader(m_ShaderProgramHandle, fragShader);

	glLinkProgram(m_ShaderProgramHandle);
#ifdef _DEBUG
	CheckShaderLinkingResult(m_ShaderProgramHandle);
#endif

	glDetachShader(m_ShaderProgramHandle, vertShader);
	glDeleteShader(vertShader);

	glDetachShader(m_ShaderProgramHandle, fragShader);
	glDeleteShader(fragShader);
}

//Debugging Helpers
void Shader::CheckShaderCompilationResult(GLuint shaderObject)
{
	GLint success;
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar info[1024];
		glGetShaderInfoLog(shaderObject, sizeof(info), nullptr, info);
		std::cerr << "Error Compiling Shader: " << std::endl;
		std::cerr << info << std::endl;
	}
}
void Shader::CheckShaderLinkingResult(GLuint shaderProgram)
{
	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == 0)
	{
		GLchar errorMsg[1024];
		glGetProgramInfoLog(shaderProgram, sizeof(errorMsg), nullptr, errorMsg);
		std::cerr << "Error Linking Shader Program: " << std::endl;
		std::cerr << errorMsg << std::endl;
	}
}

//Cache Uniforms
GLuint Shader::CacheUniformLocation(const char* name)
{
	auto it = m_UniformMap.find(name);
	if (it == m_UniformMap.end())
	{
		GLint uniformLocation = glGetUniformLocation(m_ShaderProgramHandle, name);
		m_UniformMap.insert(std::make_pair(name, uniformLocation));
	}

	return m_UniformMap[name];
}

//Get Uniforms
void Shader::GetUniform4f(const char* name, glm::vec4& value)
{
	GLint uniformLocation;
	if (!GetUniformLocation(name, &uniformLocation))
		return;

	glGetUniformfv(m_ShaderProgramHandle, uniformLocation, (GLfloat*)&value.x);
}

bool Shader::GetUniformLocation(const char* name, GLint* pLocation)
{
	auto it = m_UniformMap.find(name);
	if (it == m_UniformMap.end())
	{
		return false;
	}
	else
	{
		*pLocation = m_UniformMap[name];
		return true;
	}
}

//Set Uniforms
void Shader::SetUniform1f(const char* name, float value)
{
	glUseProgram(m_ShaderProgramHandle);
	glUniform1f(CacheUniformLocation(name), value);
	glUseProgram(0);
}
void Shader::SetUniform2f(const char* name, glm::vec2 value)
{
	glUseProgram(m_ShaderProgramHandle);
	glUniform2f(CacheUniformLocation(name), value.x, value.y);
	glUseProgram(0);
}
void Shader::SetUniform3f(const char* name, glm::vec3 value)
{
	glUseProgram(m_ShaderProgramHandle);
	glUniform3f(CacheUniformLocation(name), value.x, value.y, value.z);
	glUseProgram(0);
}
void Shader::SetUniform4f(const char* name, glm::vec4 value)
{
	glUseProgram(m_ShaderProgramHandle);
	glUniform4f(CacheUniformLocation(name), value.x, value.y, value.z, value.w);
	glUseProgram(0);
}
void Shader::SetMatrix4x4(const char* name, glm::mat4x4 value)
{
	glUniformMatrix4fv(CacheUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}