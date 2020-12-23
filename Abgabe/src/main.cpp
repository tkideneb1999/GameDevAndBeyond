#include <iostream>
#include <vector>
#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "Rendering/RenderingUtils.h"
#include "Rendering/Camera.h"
#include "Rendering/Mesh.h"

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
	
	glm::vec3 mainLightDir(1.0f, 0.0f, 0.0f);
	
	//OpenGL Setup
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);

	int width, height;
	glfwGetWindowSize(window, &width, &height);
	float aspectRatio = (float)width / (float)height;

	std::cout << "Aspect Ratio: " << aspectRatio << std::endl;

	Camera camera(45.0f, aspectRatio, 0.01f, 100.0f);
	camera.transform.transform = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f)), glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	Mesh mesh("../resources/sphere.obj");
	mesh.transform.SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));

	Mesh plane("../resources/plane.obj");
	plane.transform.SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));
	plane.SetShader("../Abgabe/resources/Shaders/ColorVert.shader", "../Abgabe/resources/Shaders/ColorFrag.shader");
	plane.shader.SetUniform4f("u_Color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	float time = 0;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		plane.DrawMesh(camera);
		mesh.transform.RotateAroundAxis(glm::vec3(0.0f, 1.0f, 1.0f), glm::radians(1.0f));
		mesh.DrawMesh(camera);

		glfwSwapBuffers(window);

		glfwPollEvents();

		//ECS Sample Code
		//RenderSystem.Render();
		time += 0.01f;
	}

	glfwTerminate();
	return 0;
}