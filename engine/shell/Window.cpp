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
	
}

void Window::Start()
{
	launchEventHandler();
}

void Window::Close()
{
	glfwSetWindowShouldClose(glfwWindow, GL_TRUE);
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
	
	while (!glfwWindowShouldClose(glfwWindow))
	{
		onBeforeRender();

		glfwPollEvents();
		calcDeltaTime();

		onRender();

		glfwSwapBuffers(glfwWindow);

		onAfterRender();
	}

	onTerminate();
}

void Window::setProperties()
{

}

void Window::calcDeltaTime()
{
	static GLdouble lastTime = 0;

	GLdouble currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}
