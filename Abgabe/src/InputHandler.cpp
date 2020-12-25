#include "InputHandler.h"

#include <iostream>

void InputHandler::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//std::cout << "Key " << glfwGetKeyName(key, scancode);
	switch (action)
	{
	case GLFW_PRESS:
		std::cout << " pressed.";
		break;
	case GLFW_REPEAT:
		std::cout << " repeated.";
		break;
	case GLFW_RELEASE:
		std::cout << " released.";
		break;
	}
	std::cout << std::endl;
}

void InputHandler::CursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{
	std::cout << "Mouse Pos:" << xPos << ", " << yPos << std::endl;
}

void InputHandler::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

}