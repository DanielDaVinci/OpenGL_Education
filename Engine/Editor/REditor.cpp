#include "REditor.h"

#include <string>


#include "Display/Frame/RFrame.h"
#include "Display/Shader/FShader.h"
#include "../objects/Camera.h"
#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_glfw.h"
#include "imGUI/imgui_impl_opengl3.h"
#include "../Engine/Runtime/GameFramework/Model/RModel.h"

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
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    const std::pair<GLint, GLint>& WindowSize = GetGLFWWindowSize(window);
    Frame = std::make_shared<RFrame>(WindowSize.first, WindowSize.second);
    
    FrameShader = std::make_shared<FShader>("Data/Shaders/frameShader.vs", "Data/Shaders/frameShader.frag");
    Shader = std::make_shared<FShader>("Data/Shaders/shader.vs", "Data/Shaders/shader.frag");

    ScreenCamera = std::make_shared<Camera>(800, 600, 45.0f);
    ScreenCamera->setAngle({ 0.0f, -90.0f, 0.0f });

    MainModel = std::make_shared<RModel>("resources/objects/backpack/backpack.obj");
}

void REditor::Tick(GLdouble DeltaTime)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    
    PreRender(DeltaTime);

    ImGui::NewFrame();
    DrawMainMenuBar();
    DrawUI(DeltaTime);
    ImGui::EndFrame();

    ImGui::Render();
    Render(DeltaTime);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    PostRender(DeltaTime);
}

void REditor::PreRender(GLdouble DeltaTime)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void REditor::Render(GLdouble DeltaTime)
{
    Frame->Bind();

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader->Use();
    Shader->setUniform("pointLight.position", ScreenCamera->getPosition());
    Shader->setUniform("pointLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
    Shader->setUniform("pointLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    Shader->setUniform("pointLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    Shader->setUniform("pointLight.constant", 1.0f);
    Shader->setUniform("pointLight.linear", 0.22f);
    Shader->setUniform("pointLight.constant", 0.20f);
    Shader->setUniform("viewPos", ScreenCamera->getPosition());

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));

    Shader->setUniform("model", model);
    Shader->setUniform("view", ScreenCamera->getViewMatrix());
    Shader->setUniform("projection", ScreenCamera->getProjectionMatrix());

    MainModel->Draw(*Shader);
    
    Frame->Bind(0);
}

void REditor::PostRender(GLdouble DeltaTime)
{
}

void REditor::DrawUI(GLdouble DeltaTime)
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    
    ImGui::Begin("MainScreen", nullptr, window_flags);

    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    ImGui::End();
    
    ImGui::Begin("Scene");
    
    const float window_width = ImGui::GetContentRegionAvail().x;
    const float window_height = ImGui::GetContentRegionAvail().y;
    
    Frame->Resize(window_width, window_height);
    glViewport(0, 0, window_width, window_height);
    // sceneCamera->setScreenWidth(window_width);
    // sceneCamera->setScreenHeight(window_height);
    
    ImVec2 pos = ImGui::GetCursorScreenPos();
    
    ImGui::GetWindowDrawList()->AddImage(
        Frame->getTextureID(),
        ImVec2(pos.x, pos.y),
        ImVec2(pos.x + window_width, pos.y + window_height),
        ImVec2(0, 1),
        ImVec2(1, 0)
    );
    
    ImGui::End();

    ImGui::ShowDemoWindow();
    
}

void REditor::DrawMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Settings"))
        {
            if (ImGui::MenuItem("Test"))
            {
                
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

std::pair<GLint, GLint> REditor::GetGLFWWindowSize(GLFWwindow* window)
{
    GLint width, height;
    glfwGetFramebufferSize(window, &width, &height);
    return std::make_pair(width, height);
}

void REditor::Exit()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
