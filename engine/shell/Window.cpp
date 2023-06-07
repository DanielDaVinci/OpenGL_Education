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
	glfwSwapInterval(1);
}

Window::~Window()
{
	
}

void Window::Start()
{
	setProperties();
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

void Window::setResizable(GLint value)
{
	resizable = value;
	setWindowHint(GLFW_RESIZABLE, value);
}

void Window::setInputMode(GLint value)
{
	inputMode = value;
	glfwSetInputMode(glfwWindow, GLFW_CURSOR, inputMode);
}

void Window::launchEventHandler()
{
	onCreate();

	glfwMakeContextCurrent(glfwWindow);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	
	while (!glfwWindowShouldClose(glfwWindow))
	{
		onBeforeRender();

		glfwPollEvents();
		calcDeltaTime();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui::NewFrame();
		onGUI();
		ImGui::EndFrame();

		ImGui::Render();
		onRender();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(glfwWindow);

		onAfterRender();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	onTerminate();
}

void Window::setProperties()
{
	setResizable(resizable);
	setInputMode(inputMode);
}

void Window::calcDeltaTime()
{
	static GLdouble lastTime = 0;

	GLdouble currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}
