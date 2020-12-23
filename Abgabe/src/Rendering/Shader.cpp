#include "Shader.h"

Shader::Shader(const char* vertShaderPath, const char* fragShaderPath)
{
	m_ShaderProgram = glCreateProgram();

	GLuint vertShader = CreateShader(vertShaderPath, GL_VERTEX_SHADER);
	GLuint fragShader = CreateShader(fragShaderPath, GL_FRAGMENT_SHADER);

	glAttachShader(m_ShaderProgram, vertShader);
	glAttachShader(m_ShaderProgram, fragShader);

	glLinkProgram(m_ShaderProgram);
#ifdef _DEBUG
	CheckShaderLinkingResult(m_ShaderProgram);
#endif

	glDetachShader(m_ShaderProgram, vertShader);
	glDeleteShader(vertShader);

	glDetachShader(m_ShaderProgram, fragShader);
	glDeleteShader(fragShader);
	std::cout << "Creating Shader" << std::endl;
}

Shader::Shader()
{
	m_ShaderProgram = glCreateProgram();

	GLuint vertShader = CreateShader("../Abgabe/resources/Shaders/DefaultVert.shader", GL_VERTEX_SHADER);
	GLuint fragShader = CreateShader("../Abgabe/resources/Shaders/DefaultFrag.shader", GL_FRAGMENT_SHADER);

	glAttachShader(m_ShaderProgram, vertShader);
	glAttachShader(m_ShaderProgram, fragShader);

	glLinkProgram(m_ShaderProgram);
#ifdef _DEBUG
	CheckShaderLinkingResult(m_ShaderProgram);
#endif

	glDetachShader(m_ShaderProgram, vertShader);
	glDeleteShader(vertShader);

	glDetachShader(m_ShaderProgram, fragShader);
	glDeleteShader(fragShader);
	std::cout << "Creating Shader" << std::endl;
}

Shader::~Shader()
{
	glDeleteProgram(m_ShaderProgram);
	std::cout << "Deleting Shader" << std::endl;
}

void Shader::EnableShader()
{
#ifdef _DEBUG
	glValidateProgram(m_ShaderProgram);
#endif
	glUseProgram(m_ShaderProgram);
}

const GLchar* Shader::LoadSource(const char* filePath)
{
	std::ifstream fileStream(filePath);

	if (fileStream.fail())
	{
		std::cerr << "Error opening Shader file at: " << filePath << std::endl;
	}

	std::string fileContent;
	std::string tempString;
	while (std::getline(fileStream, tempString, '\n'))
	{
		fileContent += tempString;
		fileContent += '\n';
	}
	GLchar* source = new GLchar[fileContent.length() + 1];
	fileContent.copy(source, fileContent.length());
	source[fileContent.length()] = '\0';

	return source;
}

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

GLuint Shader::CreateShader(const char* sourcePath, GLenum type)
{
	GLuint shaderHandle = glCreateShader(type);

	const GLchar* source = LoadSource(sourcePath);
	GLint sourceLength = strlen(source);

	glShaderSource(shaderHandle, 1, &source, &sourceLength);
	glCompileShader(shaderHandle);
	delete[] source;
#ifdef _DEBUG
	CheckShaderCompilationResult(shaderHandle);
#endif

	return shaderHandle;
}

GLuint Shader::CacheUniformLocation(const char* name)
{
	auto it = m_UniformMap.find(name);
	if (it == m_UniformMap.end())
	{
		GLuint uniformLocation = glGetUniformLocation(m_ShaderProgram, name);
		m_UniformMap.insert(std::make_pair(name, uniformLocation));
	}

	return m_UniformMap[name];
}

void Shader::SetUniform1f(const char* name, float value)
{
	glUniform1f(CacheUniformLocation(name), value);
}

void Shader::SetUniform2f(const char* name, glm::vec2 value)
{
	glUniform2f(CacheUniformLocation(name), value.x, value.y);
}

void Shader::SetUniform3f(const char* name, glm::vec3 value)
{
	glUniform3f(CacheUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetMatrix4x4(const char* name, glm::mat4x4 value)
{
	glUniformMatrix4fv(CacheUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}