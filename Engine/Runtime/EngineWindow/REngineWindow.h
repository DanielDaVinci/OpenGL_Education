#pragma once
#include "Data/FEngineWindowParameters.h"

class REngineWindow
{
    friend class REngine;
    
public:
    REngineWindow(const FEngineWindowParameters& InWindowParameters);
    ~REngineWindow();

    void Create();
    void Destroy();

    bool IsWindowShouldClose() const;
    
    static void SetWindowHint(GLint Hint, GLint Value);
    void SetWindowName(const std::string& Name);

protected:
    void SetKeyCallback(GLFWkeyfun Callback) const;
    void SetMouseButtonCallback(GLFWmousebuttonfun Callback) const;

private:
    GLFWwindow* glfwWindow = nullptr;
    FEngineWindowParameters WindowParameters;
    
};
