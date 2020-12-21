#pragma once

#include <iostream>

#include "GL/glew.h"

namespace RenderingUtils
{
	void printVersion()
	{
		GLint versionMajor, versionMinor;

		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		std::cout << "OpenGL Version: " << versionMajor << "." << versionMinor << std::endl;
	}
}