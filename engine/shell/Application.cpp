#include "Application.h"

Application::Application()
{
	GLFWCallbackWrapper::setApplication(this);
}

Application::~Application()
{
	windows.clear();
}

void Application::addWindow(Window* window)
{
	windows.push_back(window);
	setCallbacksOnWindow(window);
}

void Application::setCallbacksOnWindow(Window* window)
{
	GLFWCallbackWrapper::setCallbacksOnWindow(window->glfwWindow);
}

void Application::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	for (int i = 0; i < windows.size(); i++)
	{
		if (windows[i]->glfwWindow != window)
			continue;

		if (action == GLFW_PRESS)
			windows[i]->onKeyDown(key, scancode, mode);
		else if (action == GLFW_RELEASE)
			windows[i]->onKeyUp(key, scancode, mode);

		break;
	}
}

void Application::MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	for (int i = 0; i < windows.size(); i++)
	{
		if (windows[i]->glfwWindow != window)
			continue;

		windows[i]->onMouseDrag(xpos, ypos);
		break;
	}
}

void Application::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	for (int i = 0; i < windows.size(); i++)
	{
		if (windows[i]->glfwWindow != window)
			continue;

		windows[i]->onMouseScroll(xoffset, yoffset);
		break;
	}
}

void Application::GLFWCallbackWrapper::setApplication(Application* application)
{
	GLFWCallbackWrapper::s_application = s_application;
}

void Application::GLFWCallbackWrapper::setCallbacksOnWindow(GLFWwindow* window)
{
	glfwSetKeyCallback(window, Application::GLFWCallbackWrapper::KeyCallback);
	glfwSetCursorPosCallback(window, Application::GLFWCallbackWrapper::MousePositionCallback);
	glfwSetScrollCallback(window, Application::GLFWCallbackWrapper::MouseScrollCallback);
}

void Application::GLFWCallbackWrapper::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	s_application->KeyCallback(window, key, scancode, action, mode);
}

void Application::GLFWCallbackWrapper::MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	s_application->MousePositionCallback(window, xpos, ypos);
}

void Application::GLFWCallbackWrapper::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	s_application->MouseScrollCallback(window, xoffset, yoffset);
}
