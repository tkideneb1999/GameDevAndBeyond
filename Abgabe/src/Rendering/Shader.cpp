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
}

Shader::~Shader()
{
	
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