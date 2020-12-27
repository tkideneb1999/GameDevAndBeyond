#include "InputHandler.h"

#include <iostream>
namespace InputHandling {

	std::vector<void(*)(const char*, InputPressEnum, InputModEnum)>InputHandler::m_KeyObservers;
	
	void InputHandler::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		InputPressEnum IPE = (InputPressEnum)action;
		

		InputModEnum IME;
		switch (action)
		{
		case GLFW_MOD_SHIFT:
			IME = IME_SHIFT; break;
		case GLFW_MOD_ALT:
			IME = IME_ALT; break;
		case GLFW_MOD_CONTROL:
			IME = IME_CTRL; break;
		default:
			IME = IME_NONE; break;
		}

		const char* pressedKey = glfwGetKeyName(key, scancode);

		for(auto keyObserver : m_KeyObservers)
		{
			keyObserver(pressedKey, IPE, IME);
		}
	}

	void InputHandler::CursorPosCallback(GLFWwindow* window, double xPos, double yPos)
	{

	}

	void InputHandler::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{

	}
}