#include "RRootWindow.h"

RRootWindow::RRootWindow()
{
}

RRootWindow::~RRootWindow()
{
}

void RRootWindow::Draw()
{
    const ImGuiViewport* GUIViewport = ImGui::GetMainViewport();
    
    constexpr ImGuiWindowFlags RootWindowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
    | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    
    SetWindowFlags(RootWindowFlags);
    SetForcePosition(GUIViewport->WorkPos);
    SetForceSize(GUIViewport->WorkSize);
    SetForceViewport(GUIViewport->ID);
    
    RWindow::Draw();
}
