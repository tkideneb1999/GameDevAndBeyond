#include <iostream>
#include <vector>
#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "objSerialization/WavefrontSerialization.h"
#include "Rendering/Vertex.h"
#include "Rendering/Shader.h"
#include "Rendering/RenderingUtils.h"

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
	//int* x, y : makes only first variable a pointer, has to be written as: int* x, *y

	//const int var = 1 : cannot change var anymore -> makes it read-only
	//const int* var = 1; int const* var = 1 : cannot change content of pointer
	//int* const var = 1 : can change content, but not memory address, important const has to be after *
	//const int* const var = 1 : cannot modify anything
	//with methods: int() const : does not modify classes contents

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

	RenderingUtils::printVersion();

	glm::vec3 testVertices[4];
	testVertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
	testVertices[1] = glm::vec3(-1.0f, 1.0f, 0.0f);
	testVertices[2] = glm::vec3(1.0f, 1.0f, 0.0f);
	testVertices[3] = glm::vec3(1.0f, -1.0f, 0.0f);

	unsigned int indices[] = {
		0, 1, 2, 
		0, 2, 3,};

	//Model
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	float rotAngle = 0.0f;
	float uniformScale = 0.5f;
	glm::vec3 scale = glm::vec3(uniformScale);
	
	glm::mat4x4 model = glm::translate(glm::rotate(glm::scale(glm::mat4(1.0f), scale), rotAngle, rotationAxis), position);

	//View
	glm::vec3 CamPosition = glm::vec3(-10.0f, 0.0f, 1.0f);
	glm::vec3 camRotAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	float camRotAngle = glm::radians(-20.0f);

	glm::mat4x4 view = glm::translate(glm::rotate(glm::mat4(1.0f), camRotAngle, camRotAxis), position);

	//Projection
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	float aspectRatio = (float)width / height;
	glm::mat4x4 projection = glm::perspective(90.0f, aspectRatio, 0.01f, 100.0f);

	glm::mat4x4 MVP = model * view * projection;
	

	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(testVertices), testVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	GLuint IBO;
	glGenBuffers(1, &IBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	Shader shader("../Abgabe/resources/Shaders/DefaultVert.shader", "../Abgabe/resources/Shaders/DefaultFrag.shader");

	float time = 0;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		shader.EnableShader();
		shader.SetUniform1f("gScale", 0.5f * sinf(time) + 0.5f);
		shader.SetMatrix4x4("gMVP", MVP);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();

		//ECS Sample Code
		//RenderSystem.Render();
		time += 0.01f;
	}

	glDisableVertexAttribArray(0);

	glfwTerminate();
	return 0;
}