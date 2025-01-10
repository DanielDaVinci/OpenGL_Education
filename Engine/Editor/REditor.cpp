#include "REditor.h"

#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_glfw.h"
#include "imGUI/imgui_impl_opengl3.h"

REditor::REditor()
{
}

REditor::~REditor()
{
}

void REditor::Init(GLFWwindow* window)
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void REditor::Tick(GLdouble DeltaTime)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    PreRender(DeltaTime);

    ImGui::NewFrame();
    DrawUI(DeltaTime);
    ImGui::EndFrame();

    ImGui::Render();
    Render(DeltaTime);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    PostRender(DeltaTime);
}

void REditor::PreRender(GLdouble DeltaTime)
{
    
}

void REditor::Render(GLdouble DeltaTime)
{
    
}

void REditor::PostRender(GLdouble DeltaTime)
{
}

void REditor::DrawUI(GLdouble DeltaTime)
{
    
}

void REditor::Exit()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
