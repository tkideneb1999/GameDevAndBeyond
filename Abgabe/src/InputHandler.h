#pragma once

#include <vector>

#include "GLFW/glfw3.h"

namespace InputHandling {

	enum InputPressEnum
	{
		IPE_RELEASED = 0,
		IPE_PRESSED = 1,
		IPE_REPEAT = 2
	};

	enum InputMouseButtonEnum
	{
		IMBE_LEFT = 0,
		IMBE_RIGHT = 1,
		IMBE_MIDDLE = 2,
		IMBE_OTHER = 3
	};

	class InputHandler
	{
	private:
		static std::vector<void(*)(const char*, InputPressEnum, int)> m_KeyObservers;
		static std::vector<void(*)(double, double)> m_CursorPosObservers;
		static std::vector<void(*)(InputMouseButtonEnum, InputPressEnum, int mods)> m_MouseButtonOberservers;

	public:
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void CursorPosCallback(GLFWwindow* window, double xPos, double yPos);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	};
}