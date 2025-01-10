#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include <string>

struct FEngineWindowParameters
{
    std::string Name;
    
    GLuint Width = 0, Height = 0;
    GLint X = 0, Y = 0;

    GLint bResizable = GL_TRUE;
    GLint bCursorVisibility = GLFW_CURSOR_NORMAL;

    GLint SwapInterval = 1;
};
