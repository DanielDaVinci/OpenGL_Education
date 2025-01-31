#pragma once
#include <string>

#include "Data/FWindowData.h"
#include "Editor/UI/Widgets/RContainerWidget/RContainerWidget.h"
#include "imGUI/imgui.h"

class RWindow : public RContainerWidget
{
public:
    RWindow();
    ~RWindow() override;

    static void SetForcePosition(const ImVec2& Position);
    static void SetForceSize(const ImVec2& Size);
    static void SetForceViewport(const ImGuiID& ViewportID);

    void SetWindowFlags(const ImGuiWindowFlags& Flags);
    void SetRounding(float Radius);
    void SetBorderSize(float Size);
    void SetPaddingSize(const ImVec2& PaddingSize);

    void Draw() override;

protected:
    void PushWindowStyle() const;
    void PopWindowStyle();
    void InitDockspace();
    
private:
    FWindowData WindowData;
    
};
