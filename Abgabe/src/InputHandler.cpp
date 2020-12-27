#include "InputHandler.h"

#include <iostream>
namespace InputHandling {

	std::vector<void(*)(const char*, InputPressEnum, int)>InputHandler::m_KeyObservers;
	std::vector<void(*)(double, double)> InputHandler::m_CursorPosObservers;
	std::vector<void(*)(InputMouseButtonEnum, InputPressEnum, int mods)> InputHandler::m_MouseButtonOberservers;
	
	void InputHandler::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		InputPressEnum IPE = (InputPressEnum)action;

		const char* pressedKey = glfwGetKeyName(key, scancode);

		for(auto keyObserver : m_KeyObservers)
		{
			keyObserver(pressedKey, IPE, mods);
		}
	}

	void InputHandler::CursorPosCallback(GLFWwindow* window, double xPos, double yPos)
	{
		for (auto cursorPosObserver : m_CursorPosObservers)
		{
			cursorPosObserver(xPos, yPos);
		}
	}

	void InputHandler::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		InputMouseButtonEnum IMBE;
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			IMBE = IMBE_LEFT;
		case GLFW_MOUSE_BUTTON_RIGHT:
			IMBE = IMBE_RIGHT;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			IMBE = IMBE_MIDDLE;
		default:
			IMBE = IMBE_OTHER;
		}
		InputPressEnum IPE = (InputPressEnum)action;

		for (auto mouseButtonObserver : m_MouseButtonOberservers)
		{
			mouseButtonObserver(IMBE, IPE, mods);
		}
	}
}