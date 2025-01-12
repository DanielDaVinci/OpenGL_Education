#pragma once

#define GLEW_STATIC
#include <memory>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class RModel;
class Camera;
class FShader;
class RFrame;

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
    void DrawMainMenuBar();

protected:
    static std::pair<GLint, GLint> GetGLFWWindowSize(GLFWwindow* window);
    
private:
    std::shared_ptr<RFrame> Frame;
    std::shared_ptr<FShader> FrameShader;
    std::shared_ptr<FShader> Shader;
    std::shared_ptr<Camera> ScreenCamera;

    std::shared_ptr<RModel> MainModel;
};
