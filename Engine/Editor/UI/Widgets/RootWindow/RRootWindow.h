#pragma once
#include "Editor/UI/Widgets/Window/RWindow.h"

class RRootWindow : public RWindow
{
public:
    RRootWindow();
    ~RRootWindow();

    void Draw() override;
};
