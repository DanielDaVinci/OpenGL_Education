#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include <imGUI/imgui.h>
#include <imGUI/imgui_impl_glfw.h>
#include <imGUI/imgui_impl_opengl3.h>

#include <iostream>

class Application;

using namespace std;

class Window
{
private:

	GLFWwindow* glfwWindow = nullptr;

	string name;
	GLuint width, height;
	GLint x, y;

	GLint resizable = GL_TRUE;
	GLint inputMode = GLFW_CURSOR_NORMAL;

public:

	GLdouble deltaTime;

public:

	Window(string name = "Window", GLuint width = 800, GLuint height = 600, GLint x = 0, GLint y = 0);
	~Window();

	void Start();
	void Close();

	void setWindowHint(GLint hint, GLint value);

	// properties
	void setName(string name);
	void setPosition(GLint x, GLint y);
	void setSize(GLuint width, GLuint height);

	pair<GLdouble, GLdouble> getCursorPosition();
	pair<GLint, GLint> getFrameBufferSize();

	void setResizable(GLint value);
	void setInputMode(GLint value);

protected:

	// Lifecycle
	void launchEventHandler();

	virtual void onCreate() {};
	virtual void onBeforeRender() {};
	virtual void onGUI() {};
	virtual void onRender() {};
	virtual void onAfterRender() {};
	virtual void onTerminate() {};

	// Events
		// Mouse
	virtual void onMouseDrag(GLdouble x, GLdouble y) {};
	virtual void onMouseScroll(GLdouble xOffset, GLdouble yOffset) {};
		// KeyBoard
	virtual void onKeyDown(GLint key, GLint scanCode, GLint mode) {};
	virtual void onKeyUp(GLint key, GLint scanCode, GLint mode) {};

private:

	void setProperties();

	void calcDeltaTime();

private:

	friend Application;

};

#include "Application.h"