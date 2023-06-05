#include "Application.h"

Application::Application()
{
	glfwInit();
	GLFWCallbackWrapper::setApplication(this);

	windows = new vector<Window*>();
}

Application* Application::GLFWCallbackWrapper::s_application = nullptr;

Application::~Application()
{
	windows->clear();
	glfwTerminate();
}

void Application::addWindow(Window* window)
{
	windows->push_back(window);
	setCallbacksOnWindow(window);
	window->Start();
}

void Application::setCallbacksOnWindow(Window* window)
{
	GLFWCallbackWrapper::setApplication(this);
	GLFWCallbackWrapper::setCallbacksOnWindow(window->glfwWindow);
}

void Application::KeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mode)
{
	//cout << "asd" << endl;
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

void Application::MousePositionCallback(GLFWwindow* glfwWindow, double xpos, double ypos)
{
	for (auto window : *windows)
	{
		if (window->glfwWindow != glfwWindow)
			continue;

		window->onMouseDrag(xpos, ypos);
		break;
	}
}

void Application::MouseScrollCallback(GLFWwindow* glfwWindow, double xoffset, double yoffset)
{
	for (auto window : *windows)
	{
		if (window->glfwWindow != glfwWindow)
			continue;

		window->onMouseScroll(xoffset, yoffset);
		break;
	}
}

void Application::GLFWCallbackWrapper::setApplication(Application* application)
{
	Application::GLFWCallbackWrapper::s_application = application;
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
