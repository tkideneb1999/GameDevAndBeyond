//Third Party
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "entt/entt.hpp"

#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui.h"

//Own
#include "Rendering/RenderingUtils.h"
#include "InputHandler.h"
#include "Rendering/ShaderManager.h"

#include "Scene.h"
#include "GUI/SceneGUI.h"

#include "Serialization/SceneArchive.h"

// int* var : declares pointer -> stores address to variable
// *var		: dereferences pointer -> can change value
// int var2 : declares variable on stack
// &var2	: gets memory address of var2
// const int* p : reading possible but not modifying
// int& r : creates reference
// r->x : (*r).x
// int* x, y : makes only first variable a pointer, has to be written as: int* x, *y

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
	window = glfwCreateWindow(1280, 720, "Tiny Mini Game Engine", nullptr, nullptr);
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

	//--Glew Init
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
	
	//--OpenGL Setup
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	//--Camera Setup
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	float aspectRatio = (float)width / (float)height;

	//--Delta Time Setup
	double currentFrameTime = glfwGetTime();
	double lastFrameTime = currentFrameTime;
	double deltaTime;

	Scene scene;

	SceneGUI sceneGUI;
	
	//--Render Loop
	while (!glfwWindowShouldClose(window))
	{
		//Time handling
		currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		//ImGui BeginFrame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		sceneGUI.DrawGUI(scene);

		scene.Update(deltaTime);
		//ImGui::ShowDemoWindow();

		//ImGui EndFrame
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}