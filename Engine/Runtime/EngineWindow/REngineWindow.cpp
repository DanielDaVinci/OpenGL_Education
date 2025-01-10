#include "REngineWindow.h"

#include "GLFW/glfw3.h"

REngineWindow::REngineWindow(const FEngineWindowParameters& InWindowParameters)
{
    WindowParameters = InWindowParameters;
}

REngineWindow::~REngineWindow()
{
    
}

void REngineWindow::Create()
{
    glfwWindow = glfwCreateWindow(
        WindowParameters.Width,
        WindowParameters.Height,
        WindowParameters.Name.c_str(),
        NULL,                                   // TODO: add monitor for full screen
        NULL);
    glfwMakeContextCurrent(glfwWindow);
    glfwSwapInterval(WindowParameters.SwapInterval);
}

void REngineWindow::Destroy()
{
    glfwDestroyWindow(glfwWindow);
}

bool REngineWindow::IsWindowShouldClose() const
{
    return glfwWindowShouldClose(glfwWindow);
}

void REngineWindow::SetWindowHint(GLint Hint, GLint Value)
{
    glfwWindowHint(Hint, Value);
}

void REngineWindow::SetWindowName(const std::string& Name)
{
    WindowParameters.Name = Name;
    glfwSetWindowTitle(glfwWindow, Name.c_str());
}

void REngineWindow::SetKeyCallback(GLFWkeyfun Callback) const
{
    glfwSetKeyCallback(glfwWindow, Callback);
}

void REngineWindow::SetMouseButtonCallback(GLFWmousebuttonfun Callback) const
{
    glfwSetMouseButtonCallback(glfwWindow, Callback);
}
