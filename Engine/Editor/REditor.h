#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class REditor
{
public:
    REditor();
    ~REditor();

    void Init(GLFWwindow* window);
    void Exit();
    
    void Tick(GLdouble DeltaTime);

    void PreRender(GLdouble DeltaTime);
    void Render(GLdouble DeltaTime);
    void PostRender(GLdouble DeltaTime);

    void DrawUI(GLdouble DeltaTime);
};
