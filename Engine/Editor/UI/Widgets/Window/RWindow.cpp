#include "RWindow.h"

#include "imGUI/imgui.h"

RWindow::RWindow()
{
}

RWindow::~RWindow()
{
    
}

void RWindow::SetForcePosition(const ImVec2& Position)
{
    ImGui::SetNextWindowPos(Position);
}

void RWindow::SetForceSize(const ImVec2& Size)
{
    ImGui::SetNextWindowSize(Size);
}

void RWindow::SetForceViewport(const ImGuiID& ViewportID)
{
    ImGui::SetNextWindowViewport(ViewportID);
}

void RWindow::SetWindowFlags(const ImGuiWindowFlags& Flags)
{
    WindowData.WindowFlags |= Flags;
}

void RWindow::SetRounding(float Radius)
{
    WindowData.RoundingRadius = Radius;
}

void RWindow::SetBorderSize(float Size)
{
    WindowData.BorderSize = Size;
}

void RWindow::SetPaddingSize(const ImVec2& PaddingSize)
{
    WindowData.PaddingSize = PaddingSize;
}

void RWindow::Draw()
{
    PushWindowStyle();
    
    ImGui::Begin(WindowData.Name.c_str(), nullptr, WindowData.WindowFlags);
    
    PopWindowStyle();
    InitDockspace();
    
    RContainerWidget::Draw();
    
    ImGui::End();
}

void RWindow::PushWindowStyle() const
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, WindowData.RoundingRadius);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, WindowData.BorderSize);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, WindowData.PaddingSize);
}

void RWindow::PopWindowStyle()
{
    ImGui::PopStyleVar(3);
}

void RWindow::InitDockspace()
{
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("DockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), WindowData.DockspaceFlags);
    }
}
