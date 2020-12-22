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

	std::vector<Vertex> testVertices;
	testVertices.resize(4);
	testVertices[0].position = glm::vec3(-1.0f, -1.0f, 0.0f);
	testVertices[1].position = glm::vec3(-1.0f, 1.0f, 0.0f);
	testVertices[2].position = glm::vec3(1.0f, 1.0f, 0.0f);
	testVertices[3].position = glm::vec3(1.0f, -1.0f, 0.0f);
	testVertices[0].normal = glm::vec3(0.0f, 0.0f, 1.0f);
	testVertices[1].normal = glm::vec3(0.0f, 0.0f, 1.0f);
	testVertices[2].normal = glm::vec3(0.0f, 0.0f, 1.0f);
	testVertices[3].normal = glm::vec3(0.0f, 0.0f, 1.0f);
	testVertices[0].color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f); // purple
	testVertices[1].color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // white
	testVertices[2].color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); // red
	testVertices[3].color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // white
	testVertices[0].texcoord1 = glm::vec2(0.0f, 0.0f);
	testVertices[1].texcoord1 = glm::vec2(0.0f, 1.0f);
	testVertices[2].texcoord1 = glm::vec2(1.0f, 1.0f);
	testVertices[3].texcoord1 = glm::vec2(1.0f, 0.0f);

	std::vector<unsigned int> testIndices = {
		0, 1, 2, 
		0, 2, 3,};

	//object serialization
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	WavefrontSerialization::LoadWavefront("../resources/cube.obj", vertices, indices);

	//Model
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	float rotAngle = 0.0f;
	float uniformScale = 0.5f;
	glm::vec3 scale = glm::vec3(uniformScale);
	
	glm::mat4x4 model;

	//View
	glm::vec3 CamPosition = glm::vec3(0.0f, -3.0f, -3.0f);
	glm::mat4x4 view = glm::lookAt(CamPosition, position, glm::vec3(0.0f, 1.0f, 0.0f));

	

	//Projection
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	float aspectRatio = (float)width / (float)height;
	glm::mat4x4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.01f, 100.0f);

	glm::mat4x4 MVP;
	
	//Vertex Buffer
	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * testVertices.size(), testVertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//Index Buffer
	GLuint IBO;
	glGenBuffers(1, &IBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * testIndices.size(), testIndices.data(), GL_STATIC_DRAW);

	Shader shader("../Abgabe/resources/Shaders/DefaultVert.shader", "../Abgabe/resources/Shaders/DefaultFrag.shader");

	float time = 0;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)24);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glFrontFace(GL_CW);

		shader.EnableShader();
		rotAngle = glm::radians((time * 100));
		model = glm::translate(glm::rotate(glm::scale(glm::mat4(1.0f), scale), rotAngle, rotationAxis), position);
		MVP = projection * (view * model);

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