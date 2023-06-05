#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

#include <iostream>
#include <vector>

using namespace std;

class Application
{
private:

	vector<Window*> windows;

public:
	Application();
	~Application();

	void addWindow(Window* window);

private:

	void setCallbacksOnWindow(Window* window);

	// Callbacks
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
	void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	class GLFWCallbackWrapper
	{
	private:
		static Application* s_application;
	public:
		GLFWCallbackWrapper() = delete;
		~GLFWCallbackWrapper() = delete;

		static void setApplication(Application* application);
		static void setCallbacksOnWindow(GLFWwindow* window);

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
		static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	};
};

Application* Application::GLFWCallbackWrapper::s_application = nullptr;