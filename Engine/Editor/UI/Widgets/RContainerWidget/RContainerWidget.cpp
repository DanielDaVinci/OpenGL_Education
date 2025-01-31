#include "RContainerWidget.h"

RContainerWidget::RContainerWidget()
{
}

RContainerWidget::~RContainerWidget()
{
}

void RContainerWidget::Draw()
{
    DrawChild();
}

void RContainerWidget::DrawChild()
{
    for (const auto& Child : ChildrenWidgets)
    {
        Child->Draw();
    }
}
