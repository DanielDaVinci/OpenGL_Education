#include "GLFWindow.h"

GLFWindow::GLFWindow(int width, int height)
{
	this->width = width;
	this->height = height;

	glfwInit();
}
