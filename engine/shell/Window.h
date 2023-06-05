#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

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

	GLboolean process = GL_TRUE;

	GLboolean resizable = GL_TRUE;
	GLboolean inputMode = GL_FALSE;

public:

	GLdouble deltaTime;

public:
	Window(string name = "Window", GLuint width = 800, GLuint height = 600, GLint x = 0, GLint y = 0);
	~Window();

	void Start();

	void setWindowHint(GLint hint, GLint value);

	// properties
	void setName(string name);
	void setPosition(GLint x, GLint y);
	void setSize(GLuint width, GLuint height);

	pair<GLdouble, GLdouble> getCursorPosition();
	pair<GLint, GLint> getFrameBufferSize();

protected:
	// Lifecycle
	void launchEventHandler();

	virtual void onCreate() {};
	virtual void onBeforeRender() {};
	virtual void onRander() {};
	virtual void onAfterRender() {};
	virtual void onTerminate() {};

	// Events
		// Mouse
	virtual void onMouseDrag(GLdouble x, GLdouble y);
	virtual void onMouseScroll(GLdouble xOffset, GLdouble yOffset);
		// KeyBoard
	virtual void onKeyDown(GLint key, GLint scanCode, GLint mode);
	virtual void onKeyUp(GLint key, GLint scanCode, GLint mode);

private:
	void setProperties();

	void setEvents();

	void calcDeltaTime();
private:
	friend Application;
};

#include "Application.h"

