#include "Window.h"

Window::Window(string name, GLuint width, GLuint height, GLint x, GLint y)
{
	this->name = name;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;

	glfwWindow = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	glfwMakeContextCurrent(glfwWindow);
}

Window::~Window()
{
	glfwTerminate();
}

void Window::Start()
{
	launchEventHandler();
}

void Window::setWindowHint(GLint hint, GLint value)
{
	glfwWindowHint(hint, value);
}

void Window::setName(string name)
{
	this->name = name;
	glfwSetWindowTitle(glfwWindow, name.c_str());
}

void Window::setPosition(GLint x, GLint y)
{
	this->x = x;
	this->y = y;
	glfwSetWindowPos(glfwWindow, x, y);
}

void Window::setSize(GLuint width, GLuint height)
{
	this->width = width;
	this->height = height;
	glfwSetWindowSize(glfwWindow, width, height);
}

pair<GLdouble, GLdouble> Window::getCursorPosition()
{
	GLdouble x, y;
	glfwGetCursorPos(glfwWindow, &x, &y);
	return make_pair(x, y);
}

pair<GLint, GLint> Window::getFrameBufferSize()
{
	GLint width, height;
	glfwGetFramebufferSize(glfwWindow, &width, &height);
	return make_pair(width, height);
}

void Window::launchEventHandler()
{
	onCreate();
	
	process = GL_TRUE;

	while (process)
	{
		onBeforeRender();

		glfwPollEvents();
		calcDeltaTime();

		onRander();

		glfwSwapBuffers(glfwWindow);

		onAfterRender();
	}

	onTerminate();
}

void Window::onMouseDrag(GLdouble x, GLdouble y)
{
}

void Window::onMouseScroll(GLdouble xOffset, GLdouble yOffset)
{
}

void Window::onKeyDown(GLint key, GLint scanCode, GLint mode)
{
}

void Window::onKeyUp(GLint key, GLint scanCode, GLint mode)
{
}

void Window::setProperties()
{

}

void Window::setEvents()
{

}

void Window::calcDeltaTime()
{
	static GLdouble lastTime = 0;

	GLdouble currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}
