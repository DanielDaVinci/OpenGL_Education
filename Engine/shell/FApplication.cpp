#include "FApplication.h"

FApplication::FApplication()
{
	glfwInit();
	GLFWCallbackWrapper::setApplication(this);

	windows = new vector<Window*>();
}

FApplication* FApplication::GLFWCallbackWrapper::s_application = nullptr;

FApplication::~FApplication()
{
	windows->clear();
	glfwTerminate();
}

void FApplication::addWindow(Window* window)
{
	windows->push_back(window);
	setCallbacksOnWindow(window);

	window->Start();
}

void FApplication::setCallbacksOnWindow(Window* window)
{
	GLFWCallbackWrapper::setApplication(this);
	GLFWCallbackWrapper::setCallbacksOnWindow(window->glfwWindow);
}

void FApplication::KeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mode)
{
	for (auto window : *windows)
	{
		if (window->glfwWindow != glfwWindow)
			continue;

		if (action == GLFW_PRESS)
			window->onKeyDown(key, scancode, mode);
		else if (action == GLFW_RELEASE)
			window->onKeyUp(key, scancode, mode);

		break;
	}
}

void FApplication::MousePositionCallback(GLFWwindow* glfwWindow, double xpos, double ypos)
{
	for (auto window : *windows)
	{
		if (window->glfwWindow != glfwWindow)
			continue;

		window->onMouseDrag(xpos, ypos);
		break;
	}
}

void FApplication::MouseScrollCallback(GLFWwindow* glfwWindow, double xoffset, double yoffset)
{
	for (auto window : *windows)
	{
		if (window->glfwWindow != glfwWindow)
			continue;

		window->onMouseScroll(xoffset, yoffset);
		break;
	}
}

void FApplication::GLFWCallbackWrapper::setApplication(FApplication* application)
{
	FApplication::GLFWCallbackWrapper::s_application = application;
}

void FApplication::GLFWCallbackWrapper::setCallbacksOnWindow(GLFWwindow* window)
{
	glfwSetKeyCallback(window, FApplication::GLFWCallbackWrapper::KeyCallback);
	glfwSetCursorPosCallback(window, FApplication::GLFWCallbackWrapper::MousePositionCallback);
	glfwSetScrollCallback(window, FApplication::GLFWCallbackWrapper::MouseScrollCallback);
}

void FApplication::GLFWCallbackWrapper::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	s_application->KeyCallback(window, key, scancode, action, mode);
}

void FApplication::GLFWCallbackWrapper::MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	s_application->MousePositionCallback(window, xpos, ypos);
}

void FApplication::GLFWCallbackWrapper::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	s_application->MouseScrollCallback(window, xoffset, yoffset);
}
