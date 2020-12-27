#pragma once

#include <vector>

#include "GLFW/glfw3.h"

namespace InputHandling {
	enum InputModEnum
	{
		IME_NONE = 0,
		IME_SHIFT = 1,
		IME_ALT = 2,
		IME_CTRL = 3
	};

	enum InputPressEnum
	{
		IPE_RELEASED = 0,
		IPE_PRESSED = 1,
		IPE_REPEAT = 2
	};

	class InputHandler
	{
	private:
		std::vector<void(*)(const char*, InputPressEnum, InputModEnum)> m_KeyObservers;

	public:
		void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void CursorPosCallback(GLFWwindow* window, double xPos, double yPos);
		void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	};
}