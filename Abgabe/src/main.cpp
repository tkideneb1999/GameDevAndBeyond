#include <iostream>
#include <vector>
#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "objSerialization/WavefrontSerialization.h"
#include "Rendering/Vertex.h"

int main()
{
	GLFWwindow* window;

	//Initialize Library
	if (!glfwInit())
		return -1;

	//Create a windowed mode window and its OpenGL Context
	window = glfwCreateWindow(1280, 720, "GLFW", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//object serialization
	//std::vector<Vertex> vertices;
	//std::vector<unsigned int> indices;
	//WavefrontSerialization::LoadWavefront("../resources/cube.obj", vertices, indices);

	// int* var : declares pointer -> stores address to variable
	// *var		: dereferences pointer -> can change value
	// int var2 : declares variable on stack
	// &var2	: gets memory address of var2
	// const int* p : reading possible but not modifying
	// int& r : creates reference
	// r->x : (*r).x

	//ECS Sample Code
	//Entity entity;
	//entity.AddComponent<SampleComponent>();
	//entity.RemoveComponent<SampleComponent>();
	//entity.SampleComponent.position.x = 0.1f;

	// Make the window's context current
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;

	glm::vec3 testVertices[3];
	testVertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
	testVertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
	testVertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);

	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(testVertices), testVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	GLuint shaderProgram = glCreateProgram();
	GLuint vertShaderObject = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertShaderSource = "";
	std::string fragShaderSource = "";

	const GLchar* const* test = vertShaderSource.c_str();
	GLint testInt;

	glShaderSource(vertShaderObject, 1, test,vertShaderSource.length());

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);

		glfwPollEvents();

		//ECS Sample Code
		//RenderSystem.Render();
	}

	glDisableVertexAttribArray(0);

	glfwTerminate();
	return 0;
}