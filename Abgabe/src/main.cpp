#include <iostream>
#include <vector>
#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "entt/entt.hpp"

#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui.h"

#include "Rendering/RenderSystem.h"
#include "Rendering/Camera.h"
#include "Rendering/Mesh.h"
#include "Rendering/RenderingUtils.h"
#include "InputHandler.h"
#include "Rendering/Material.h"
#include "Rendering/ShaderManager.h"

#include "Scene.h"
#include "GUI/SceneGUI.h"

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

int main()
{
	GLFWwindow* window;

	//--Initialize GLFW Library
	if (!glfwInit())
		return -1;

#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, true);

	//--Create a windowed mode window and its OpenGL Context
	window = glfwCreateWindow(1280, 720, "Open GL Renderer", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//--Make the window's context current
	glfwMakeContextCurrent(window);

	//--Input Handling
	InputHandling::InputHandler inputHandler;
	
	glfwSetKeyCallback(window, inputHandler.KeyCallback);
	glfwSetCursorPosCallback(window, inputHandler.CursorPosCallback);
	glfwSetMouseButtonCallback(window, inputHandler.MouseButtonCallback);

	GLenum err = glewInit();
	if (GLEW_OK != err)
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;

	//--Init ImGUI
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	//--Debug Messaging System
#ifdef _DEBUG
	GLint openGLFlags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &openGLFlags);
	if (openGLFlags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(RenderingUtils::glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	//--Print Info
	RenderingUtils::printInfo();
#endif
	
	//--Register Shaders
	ShaderManager& shaderManager = ShaderManager::Get();
	shaderManager.RegisterShader("../Abgabe/resources/Shaders/Default.shader");
	shaderManager.RegisterShader("../Abgabe/resources/Shaders/Lambert.shader");

	//--EnTT ECS Init
	entt::registry registry;
	
	//--OpenGL Setup
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	RenderSystem renderSystem;

	glm::vec3 mainLightDir(0.0f, 1.0f, 0.0f);

	//--Camera Setup
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	float aspectRatio = (float)width / (float)height;

	//--Camera Entity
	entt::entity camera = registry.create();
	auto& camTransform = registry.emplace<Transform>(camera, glm::vec3(0.0f, 0.0f, 4.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
	auto& camComponent = registry.emplace<Camera>(camera, 45.0f, aspectRatio, 0.01f, 100.0f);

	//--Mesh Entities
	std::cout << "-------------" << std::endl;
	std::cout << "Creating Entity Plane" << std::endl;
	entt::entity plane = registry.create();
	auto& planeTransform = registry.emplace<Transform>(plane);
	planeTransform.SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));
	auto& planeMesh = registry.emplace<Mesh>(plane, "../resources/plane.obj");
	planeMesh.SetMaterial("../resources/Materials/Default.mat");

	std::cout << "-------------" << std::endl;
	std::cout << "Creating Entity Suzanne" << std::endl;
	entt::entity suzanne = registry.create();
	registry.emplace<Transform>(suzanne);
	auto& suzanneMesh = registry.emplace<Mesh>(suzanne, "../resources/suzanne.obj");
	suzanneMesh.SetMaterial("../resources/Materials/Lambert.mat");
	suzanneMesh.material.SetUniform("u_LightDir", mainLightDir);

	float imGuiFloat = 0;

	Scene scene;
	SceneGUI sceneGUI;
	
	//--Render Loop
	while (!glfwWindowShouldClose(window))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		sceneGUI.DrawGUI(scene);

		//ImGui::ShowDemoWindow();
		renderSystem.Render(registry);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}