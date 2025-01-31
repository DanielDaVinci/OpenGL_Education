#pragma once

#define GLEW_STATIC
#include <memory>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class RRootWindow;
class RWidget;
class RModel;
class RCamera;
class FShader;
class RFrame;

class REditor
{
public:
    REditor();
    ~REditor();
    
    void Init(GLFWwindow* window);
    void Exit();

    void PreTick(GLdouble DeltaTime);
    void Tick(GLdouble DeltaTime);

    void PreRender(GLdouble DeltaTime);
    void Render(GLdouble DeltaTime);
    void PostRender(GLdouble DeltaTime);

    void DrawUI(GLdouble DeltaTime);
    void DrawMainMenuBar();

    void OnKeyDown(int key, int scancode, int mode);
    void OnKeyUp(int key, int scancode, int mode);

    void OnMouseDown(int button, int mods);
    void OnMouseUp(int button, int mods);

protected:
    static std::pair<GLint, GLint> GetGLFWWindowSize(GLFWwindow* window);

    void Move(GLdouble DeltaTime) const;
    
private:
    std::shared_ptr<RFrame> Frame;
    std::shared_ptr<FShader> FrameShader;
    std::shared_ptr<FShader> Shader;
    std::shared_ptr<RCamera> ScreenCamera;

    std::shared_ptr<RModel> MainModel;
    std::shared_ptr<RRootWindow> RootWidget;

    GLboolean Keys[1024] = {};
};
